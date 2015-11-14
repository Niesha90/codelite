#include "ExternalToolsProcessManager.h"
#include "event_notifier.h"
#include "globals.h"
#include "imanager.h"
#include "asyncprocess.h"
#include "macromanager.h"
#include "environmentconfig.h"
#include "processreaderthread.h"
#include <algorithm>
#include <wx/utils.h>
#include <wx/process.h>
#include <wx/msgdlg.h>

/**
 * @class MyProcess
 * @brief handler class for capturing non-redirected processes termination
 */
class MyProcess : public wxProcess
{
public:
    MyProcess() {}
    virtual ~MyProcess() {}
    void OnTerminate(int pid, int status)
    {
        ToolsTaskManager::Instance()->ProcessTerminated(pid);
        delete this;
    }
};

ToolsTaskManager* ToolsTaskManager::ms_instance = 0;

ToolsTaskManager::ToolsTaskManager()
{
    Bind(wxEVT_ASYNC_PROCESS_OUTPUT, &ToolsTaskManager::OnProcessOutput, this);
    Bind(wxEVT_ASYNC_PROCESS_TERMINATED, &ToolsTaskManager::OnProcessEnd, this);
}

ToolsTaskManager::~ToolsTaskManager()
{
    Unbind(wxEVT_ASYNC_PROCESS_OUTPUT, &ToolsTaskManager::OnProcessOutput, this);
    Unbind(wxEVT_ASYNC_PROCESS_TERMINATED, &ToolsTaskManager::OnProcessEnd, this);
}

ToolsTaskManager* ToolsTaskManager::Instance()
{
    if(ms_instance == 0) {
        ms_instance = new ToolsTaskManager();
    }
    return ms_instance;
}

void ToolsTaskManager::Release()
{
    if(ms_instance) {
        delete ms_instance;
    }
    ms_instance = 0;
}

void ToolsTaskManager::OnProcessEnd(clProcessEvent& event)
{
    clGetManager()->AppendOutputTabText(kOutputTab_Output, event.GetOutput());
    clGetManager()->AppendOutputTabText(kOutputTab_Output, "\n");

    // delete the process
    IProcess* proc = event.GetProcess();
    ProcessTerminated(proc->GetPid());
    delete proc;

    // Notify codelite to test for any modified bufferes
    EventNotifier::Get()->PostReloadExternallyModifiedEvent();
}

void ToolsTaskManager::OnProcessOutput(clProcessEvent& event)
{
    clGetManager()->AppendOutputTabText(kOutputTab_Output, event.GetOutput());
}

void ToolsTaskManager::StartTool(const ToolInfo& ti)
{
    wxString command, working_dir;
    command << ti.GetPath();
    ::WrapWithQuotes(command);

    command << " " << ti.GetArguments();
    working_dir = ti.GetWd();

    command = MacroManager::Instance()->Expand(
        command,
        clGetManager(),
        (clGetManager()->GetWorkspace() ? clGetManager()->GetWorkspace()->GetActiveProjectName() : ""));
    working_dir = MacroManager::Instance()->Expand(
        working_dir,
        clGetManager(),
        (clGetManager()->GetWorkspace() ? clGetManager()->GetWorkspace()->GetActiveProjectName() : ""));

    wxString projectName;
    wxString configName;
    if(clCxxWorkspaceST::Get()->IsOpen()) {
        projectName = clCxxWorkspaceST::Get()->GetActiveProjectName();
        BuildConfigPtr bldConf = clCxxWorkspaceST::Get()->GetProjBuildConf(projectName, wxEmptyString);
        if(bldConf) {
            configName = bldConf->GetName();
        }
    }

    EnvSetter envGuard(clGetManager()->GetEnv(), NULL, projectName, configName);
    //::WrapInShell(command);
    
    int pid = wxNOT_FOUND;
    if(ti.GetCaptureOutput()) {
        IProcess* proc = ::CreateAsyncProcess(this, command, IProcessCreateConsole, working_dir);
        if(!proc) {
            ::wxMessageBox(_("Failed to launch tool\n'") + command + "'",
                           "CodeLite",
                           wxICON_ERROR | wxOK | wxCENTER,
                           EventNotifier::Get()->TopFrame());
            return;
        }

        pid = proc->GetPid();

    } else {
        pid = ::wxExecute(command, wxEXEC_ASYNC | wxEXEC_MAKE_GROUP_LEADER, new MyProcess());
    }
    
    if(pid > 0) {
        ExternalToolItemData item(command, pid);
        m_tools.insert(std::make_pair(pid, item));
    }
}

void ToolsTaskManager::ProcessTerminated(int pid)
{
    if(m_tools.find(pid) != m_tools.end()) {
        m_tools.erase(pid);
    }
}

void ToolsTaskManager::StopAll()
{
    std::for_each(m_tools.begin(), m_tools.end(), [&](const std::pair<int, ExternalToolItemData> &p) {
        ::wxKill(p.second.m_pid, wxSIGKILL, NULL, wxKILL_CHILDREN);
    });
}

void ToolsTaskManager::Stop(int pid)
{
    if(m_tools.find(pid) != m_tools.end()) {
        ::wxKill(pid, wxSIGKILL, NULL, wxKILL_CHILDREN);
    }
}
