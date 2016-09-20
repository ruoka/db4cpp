#include <csignal>
#include <experimental/string_view>
#include "std/span.hpp"
#include "net/syslogstream.hpp"
#include "db/rest/server.hpp"

using namespace std;
using namespace experimental;
using namespace string_literals;
using namespace net;

const auto usage = R"(yardb [--help] [--slog_tag=<tag>] [--slog_level=<level>] [--clog] [service_or_port])";

int main(int argc, char** argv)
try
{
    std::signal(SIGTERM, std::exit); // Handle kill
    std::signal(SIGINT,  std::exit); // Handle ctrl-c

    const auto arguments = span<char*>{argv,argc}.subspan(1);
    auto service_or_port = "2112"s;
    slog.tag("YarDB");
    slog.level(net::syslog::severity::debug);

    for(const string_view option : arguments)
    {
        if(option.find("--slog_tag=") == 0)
        {
            const auto name = option.substr(option.find('=')+1).to_string();
            slog.tag(name);
        }
        else if(option.find("--slog_level=") == 0)
        {
            const auto mask = stol(option.substr(option.find('=')+1));
            slog.level(mask);
        }
        else if(option.find("--clog") == 0)
        {
            slog.redirect(clog);
        }
        else if(option.find("--help") == 0)
        {
            clog << usage << endl;
            return 0;
        }
        else if(option.find("-") == 0)
        {
            clog << usage << endl;
            return 1;
        }
        else
        {
            service_or_port = option.to_string();
        }
    }

    slog << notice << "Initializing server" << flush;
    auto engine = db::engine{};
    auto server = db::rest::server{engine};
    slog << notice << "Initialized server" << flush;
    server.start(service_or_port);
    slog << notice << "Closed server" << flush;
    return 0;
}
catch(const system_error& e)
{
    slog << error << "System error with code " << e.code() << " " << e.what() << flush;
    return 1;
}
catch(const exception& e)
{
    slog << error << "Exception " << e.what() << flush;
    return 1;
}
catch(...)
{
    slog << error << "Shit hit the fan!" << flush;
    return 1;
}
