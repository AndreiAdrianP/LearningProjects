#include "Icommand.hpp"
#include "HeadLightSimulation.hpp"

void execute_commands(HeadlightContext& context, const std::vector<std::unique_ptr<ICommand>>& commands) {
    std::cout << "\n[Invoker] Processing Command Sequence..." << std::endl;
    for (const auto& command : commands) {
        std::cout << "\n--- EXECUTE COMMAND: " << command->get_name() << " ---" << std::endl;
        command->execute(context);
    }
}
