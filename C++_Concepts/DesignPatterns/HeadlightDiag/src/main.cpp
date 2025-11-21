#include "Icommand.hpp"
#include "HeadLightSimulation.hpp"

int main() {
    // 1. Receiver: The Headlight Control Unit (ECU)
    HeadlightContext headlight_ecu;
    DashboardDisplay display_service;
    DiagnosticLogger logger_service;
    std::cout << "\n[Client] Attaching Dashboard and Logger services." << std::endl;
    headlight_ecu.attach(&display_service);
    headlight_ecu.attach(&logger_service);

    // 2. Command Sequence (Invoker/Client creating commands)
    std::vector<std::unique_ptr<ICommand>> command_sequence;

    // Command 1: Turn on Low Beams
    command_sequence.push_back(std::make_unique<ToggleLowBeamCommand>());
    
    // Command 2: Turn on High Beams
    command_sequence.push_back(std::make_unique<ToggleHighBeamCommand>());
    
    // Command 3: Try to enable Auto Mode (valid action in this state)
    command_sequence.push_back(std::make_unique<ToggleAutoModeCommand>());

    // Command 4: Turn off High Beams (back to Low Beam, or directly Off? Let state decide)
    command_sequence.push_back(std::make_unique<SwitchOffCommand>());

    // Command 5: Turn off Low Beams
    command_sequence.push_back(std::make_unique<SwitchOffCommand>());


    // 3. Execution
    execute_commands(headlight_ecu, command_sequence);
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "[Client] Detaching Logger service for maintenance." << std::endl;
    headlight_ecu.detach(&logger_service);
    std::cout << "=======================================================" << std::endl;
    
    // 7. Final command after detachment (ONLY DashboardDisplay should update)
    std::cout << "\n--- EXECUTE COMMAND: Toggle Low Beam (Post Detach) ---" << std::endl;
    ToggleLowBeamCommand().execute(headlight_ecu);


    std::cout << "\n--- Simulation Finished ---" << std::endl;
    std::cout << "Final Auto Mode Status: " << (headlight_ecu.is_auto_mode() ? "Active" : "Inactive") << std::endl;
    
    return 0;
}