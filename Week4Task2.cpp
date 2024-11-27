#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm> // for std::copy and std::find

int main() {
    // Step 1: Populate Containers
    std::vector<std::string> dynamicWidgets = {"Speedometer", "Tachometer", "FuelGauge", "Odometer"};
    std::set<std::string> staticWidgets = {"Logo", "WarningLights", "NavigationIcons"};

    // Step 2: Use Iterators to Print Dynamic Widgets
    std::cout << "Dynamic Widgets:\n";
    for (auto it = dynamicWidgets.begin(); it != dynamicWidgets.end(); ++it) {
        std::cout << "- " << *it << '\n';
    }

    // Step 3: Check if a Specific Widget is in the std::set
    std::string searchWidget = "WarningLights";
    auto foundInSet = staticWidgets.find(searchWidget);

    if (foundInSet != staticWidgets.end()) {
        std::cout << "\nWidget \"" << searchWidget << "\" is in the static widgets.\n";
    } else {
        std::cout << "\nWidget \"" << searchWidget << "\" is not in the static widgets.\n";
    }

    // Step 4: Advanced Iteration - Combine Both Containers
    std::vector<std::string> combinedWidgets;
    combinedWidgets.reserve(dynamicWidgets.size() + staticWidgets.size()); // Reserve space for efficiency

    std::copy(dynamicWidgets.begin(), dynamicWidgets.end(), std::back_inserter(combinedWidgets));
    std::copy(staticWidgets.begin(), staticWidgets.end(), std::back_inserter(combinedWidgets));

    // Use std::find to Locate a Specific Widget in Combined Container
    std::string widgetToFind = "Odometer";
    auto foundInCombined = std::find(combinedWidgets.begin(), combinedWidgets.end(), widgetToFind);

    // Step 5: Output Results
    std::cout << "\nCombined Widget List:\n";
    for (const auto& widget : combinedWidgets) {
        std::cout << "- " << widget << '\n';
    }

    if (foundInCombined != combinedWidgets.end()) {
        std::cout << "\nWidget \"" << widgetToFind << "\" found in the combined list.\n";
    } else {
        std::cout << "\nWidget \"" << widgetToFind << "\" not found in the combined list.\n";
    }

    return 0;
}
