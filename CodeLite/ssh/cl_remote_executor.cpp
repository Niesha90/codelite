#if USE_SFTP
#include "ssh/cl_remote_executor.hpp"

#include "StringUtils.h"
#include "clModuleLogger.hpp"
#include "cl_standard_paths.h"
#include "processreaderthread.h"
#include "ssh/clRemoteHost.hpp"
#include "ssh/ssh_account_info.h"

#include <thread>
INITIALISE_SSH_LOG(EXECLOG, "clRemoteExecutor");

clRemoteExecutor::clRemoteExecutor() {}

clRemoteExecutor::~clRemoteExecutor() { shutdown(); }

void clRemoteExecutor::execute_with_callback(const clRemoteExecutor::Cmd& cmd, const wxString& account,
                                             execute_callback&& cb)
{
    auto ssh_session = clRemoteHost::Instance()->GetSshSession();
    if(!ssh_session) {
        LOG_WARNING(EXECLOG) << "SSH session is not opened" << endl;
        return;
    }

    // open the channel
    clSSHChannel* channel = new clSSHChannel(this, ssh_session, true);
    if(!channel->Open()) {
        wxDELETE(channel);
        return;
    }

    wxString command = ssh::build_command(cmd.command, cmd.wd, cmd.env);
    LOG_DEBUG(EXECLOG) << "Executing command:" << command << endl;

    // prepare the commands
    if(!channel->Execute(command, std::move(cb))) {
        wxDELETE(channel);
        return;
    }
    LOG_DEBUG(EXECLOG) << "Success" << endl;
    m_runningCommands.insert(channel);
}

void clRemoteExecutor::shutdown()
{
    while(!m_runningCommands.empty()) {
        clSSHChannel* channel = (*m_runningCommands.begin());
        delete channel;
        m_runningCommands.erase(m_runningCommands.begin());
    }
}
void clRemoteExecutor::Delete(clSSHChannel* channel)
{
    auto iter = m_runningCommands.find(channel);
    if(iter != m_runningCommands.end()) {
        auto p_channel = *iter;
        delete p_channel;
        m_runningCommands.erase(iter);
    }
}
bool clRemoteExecutor::execute_command(const clRemoteExecutor::Cmd& cmd, const wxString& account, std::string* output)
{
    auto ssh_session = clRemoteHost::Instance()->GetSshSession();
    if(!ssh_session) {
        LOG_WARNING(EXECLOG) << "SSH session is not opened" << endl;
        return false;
    }

    // open the channel
    clSSHChannel* channel = new clSSHChannel(this, ssh_session, true);
    if(!channel->Open()) {
        wxDELETE(channel);
        return false;
    }

    wxString command = ssh::build_command(cmd.command, cmd.wd, cmd.env);
    LOG_DEBUG(EXECLOG) << "Executing command:" << command << endl;

    // prepare the commands
    if(!channel->Execute(command, output)) {
        wxDELETE(channel);
        return false;
    }
    LOG_DEBUG(EXECLOG) << "Success" << endl;
    return true;
}

clSSHChannel* clRemoteExecutor::execute(const clRemoteExecutor::Cmd& cmd, const wxString& account,
                                        wxEvtHandler* event_handler)
{
    auto ssh_session = clRemoteHost::Instance()->GetSshSession();
    if(!ssh_session) {
        LOG_WARNING(EXECLOG) << "SSH session is not opened" << endl;
        return nullptr;
    }

    // open the channel
    clSSHChannel* channel = new clSSHChannel(this, ssh_session, true);
    if(!channel->Open()) {
        wxDELETE(channel);
        return nullptr;
    }

    wxString command = ssh::build_command(cmd.command, cmd.wd, cmd.env);
    LOG_DEBUG(EXECLOG) << "Executing command:" << command << endl;

    // prepare the commands
    if(!channel->Execute(command, event_handler)) {
        wxDELETE(channel);
        return nullptr;
    }
    LOG_DEBUG(EXECLOG) << "Success" << endl;
    return channel;
}

#endif // USE_SFTP