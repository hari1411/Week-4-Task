#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Control {
    int id;               // Unique ID
    std::string type;     // "button" or "slider"
    std::string state;    // "visible", "invisible", "disabled"
};

int main() {
    std::vector<Control> controls = {
        {1, "button", "visible"},
        {2, "button", "invisible"},
        {3, "slider", "disabled"},
        {4, "button", "visible"},
        {5, "slider", "disabled"},
        {6, "button", "visible"},
        {7, "slider", "visible"},
        {8, "button", "invisible"},
        {9, "slider", "visible"},
        {10, "slider", "visible"}
    };

    std::cout << "All controls:\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) {
        std::cout << "ID: " << ctrl.id 
                  << ", Type: " << ctrl.type 
                  << ", State: " << ctrl.state << '\n';
    });

    int searchID = 3; // Example: searching for ID 3
    auto it = std::find_if(controls.begin(), controls.end(), [searchID](const Control& ctrl) {
        return ctrl.id == searchID;
    });

    if (it != controls.end()) {
        std::cout << "\nControl with ID " << searchID << " found: "
                  << "Type: " << it->type 
                  << ", State: " << it->state << '\n';
    } else {
        std::cout << "\nControl with ID " << searchID << " not found.\n";
    }

    auto invisibleControl = std::find_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "invisible";
    });

    if (invisibleControl != controls.end()) {
        std::cout << "\nFirst invisible control found: "
                  << "ID: " << invisibleControl->id 
                  << ", Type: " << invisibleControl->type << '\n';
    } else {
        std::cout << "\nNo invisible controls found.\n";
    }

    if (controls.size() >= 2) {
        auto consecutiveControls = std::adjacent_find(controls.begin(), controls.end(), [](const Control& a, const Control& b) {
            return a.state == b.state;
        });

        if (consecutiveControls != controls.end()) {
            std::cout << "\nConsecutive controls with the same state found: "
                      << "ID: " << consecutiveControls->id 
                      << " and ID: " << std::next(consecutiveControls)->id
                      << ", State: " << consecutiveControls->state << '\n';
        } else {
            std::cout << "\nNo consecutive controls with the same state found.\n";
        }
    }

    int visibleCount = std::count_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "visible";
    });

    std::cout << "\nNumber of visible controls: " << visibleCount << '\n';

    int disabledSliders = std::count_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.type == "slider" && ctrl.state == "disabled";
    });

    std::cout << "\nNumber of disabled sliders: " << disabledSliders << '\n';

    if (controls.size() >= 4) {
        bool areSubrangesEqual = std::equal(controls.begin(), controls.begin() + 2, controls.begin() + 2, [](const Control& a, const Control& b) {
            return a.state == b.state && a.type == b.type;
        });

        std::cout << "\nAre the first two controls equal to the next two? " 
                  << (areSubrangesEqual ? "Yes" : "No") << '\n';
    } else {
        std::cout << "\nNot enough controls to compare subranges.\n";
    }

    return 0;
}

