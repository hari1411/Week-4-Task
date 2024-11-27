#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

struct Control {
    int id;               // Unique ID
    std::string type;     // "button" or "slider"
    std::string state;    // "visible", "invisible", "disabled"
};

// Helper function to print the controls
void printControls(const std::vector<Control>& controls, const std::string& message) {
    std::cout << message << "\n";
    for (const auto& ctrl : controls) {
        std::cout << "ID: " << ctrl.id
                  << ", Type: " << ctrl.type
                  << ", State: " << ctrl.state << '\n';
    }
    std::cout << '\n';
}

int main() {
    // Initialize Controls
    std::vector<Control> controls = {
        {1, "button", "visible"},
        {2, "slider", "visible"},
        {3, "button", "disabled"},
        {4, "slider", "invisible"},
        {5, "slider", "visible"},
    };

    // Step 1: Manipulate Control States
    // Backup original list using std::copy
    std::vector<Control> backupControls;
    std::copy(controls.begin(), controls.end(), std::back_inserter(backupControls));
    printControls(backupControls, "Backup of Original Controls:");

    // Set all states to "disabled" temporarily using std::fill
    std::fill(controls.begin(), controls.end(), Control{0, "", "disabled"});
    printControls(controls, "After std::fill (all states set to disabled):");

    // Generate random states for testing using std::generate
    std::vector<std::string> possibleStates = {"visible", "invisible", "disabled"};
    std::srand(static_cast<unsigned>(std::time(0))); // Seed for randomness
    std::generate(controls.begin(), controls.end(), [&]() {
        return Control{
            std::rand() % 100, // Random ID
            "slider",          // All sliders for this test
            possibleStates[std::rand() % possibleStates.size()]};
    });
    printControls(controls, "After std::generate (random states):");

    // Step 2: Apply Transformations
    // Use std::transform to change all sliders' state to "invisible"
    std::transform(controls.begin(), controls.end(), controls.begin(), [](Control& ctrl) {
        if (ctrl.type == "slider") ctrl.state = "invisible";
        return ctrl;
    });
    printControls(controls, "After std::transform (sliders set to invisible):");

    // Use std::replace to change "disabled" to "enabled"
    std::replace_if(controls.begin(), controls.end(),
        [](const Control& ctrl) { return ctrl.state == "disabled"; },
        Control{0, "", "enabled"});
    printControls(controls, "After std::replace (disabled -> enabled):");

    // Use std::remove_if to filter out invisible controls
    auto newEnd = std::remove_if(controls.begin(), controls.end(),
        [](const Control& ctrl) { return ctrl.state == "invisible"; });
    controls.erase(newEnd, controls.end());
    printControls(controls, "After std::remove_if (invisible controls removed):");

    // Step 3: Other Operations
    // Reverse the control order using std::reverse
    std::reverse(controls.begin(), controls.end());
    printControls(controls, "After std::reverse (controls reversed):");

    // Group visible controls together using std::partition
    std::partition(controls.begin(), controls.end(),
        [](const Control& ctrl) { return ctrl.state == "visible"; });
    printControls(controls, "After std::partition (visible controls grouped):");

    return 0;
}
