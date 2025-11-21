#include "Icommand.hpp"
#include "HeadLightSimulation.hpp"




// --- ToggleLowBeamCommand Implementation ---
void ToggleLowBeamCommand::execute(HeadlightContext& context) {
    std::cout << "Context received input: switch_to_low" << std::endl;
    context.process_event("switch_to_low");
}
std::string ToggleLowBeamCommand::get_name() const { 
    return "Toggle Low Beam"; 
}

// --- ToggleHighBeamCommand Implementation ---
void ToggleHighBeamCommand::execute(HeadlightContext& context) {
    std::cout << "Context received input: switch_to_high" << std::endl;
    context.process_event("switch_to_high"); 
}
std::string ToggleHighBeamCommand::get_name() const { 
    return "Toggle High Beam"; 
}

// --- SwitchOffCommand Implementation ---
void SwitchOffCommand::execute(HeadlightContext& context) {
    std::cout << "Context received input: switch_to_off" << std::endl;
    context.process_event("switch_to_off");
}
std::string SwitchOffCommand::get_name() const { 
    return "Switch Off"; 
}

// --- ToggleAutoModeCommand Implementation ---
void ToggleAutoModeCommand::execute(HeadlightContext& context) {
    std::cout << "Context received input: toggle_auto" << std::endl;
    context.process_event("toggle_auto");
}
std::string ToggleAutoModeCommand::get_name() const { 
    return "Toggle Auto Mode"; 
}

// --- Utility Function Implementation ---
void execute_commands(HeadlightContext& context, const std::vector<std::unique_ptr<ICommand>>& commands) {
    std::cout << "\n[Invoker] Processing Command Sequence..." << std::endl;
    for (const auto& command : commands) {
        std::cout << "\n--- EXECUTE COMMAND: " << command->get_name() << " ---" << std::endl;
        command->execute(context);
    }
}