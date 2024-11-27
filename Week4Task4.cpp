#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

struct Control {
    int id;               // Unique ID
    std::string type;     // "button" or "slider"
    std::string state;    // "visible", "invisible", "disabled"

    // Overload < operator for sorting by ID
    bool operator<(const Control& other) const {
        return id < other.id;
    }
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
    // Initialize two lists of controls
    std::vector<Control> list1 = {
        {1, "button", "visible"},
        {3, "slider", "invisible"},
        {5, "button", "disabled"},
    };
    std::vector<Control> list2 = {
        {2, "slider", "visible"},
        {3, "slider", "disabled"},
        {4, "button", "invisible"},
    };

    // Step 1: Sorting
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());
    printControls(list1, "List 1 after sorting by ID:");
    printControls(list2, "List 2 after sorting by ID:");

    // Use std::stable_sort to maintain relative order for equal IDs
    std::stable_sort(list2.begin(), list2.end(), [](const Control& a, const Control& b) {
        return a.id < b.id;
    });
    printControls(list2, "List 2 after stable sorting by ID:");

    // Step 2: Binary Search
    int searchID = 3;
    auto lower = std::lower_bound(list2.begin(), list2.end(), Control{searchID, "", ""});
    auto upper = std::upper_bound(list2.begin(), list2.end(), Control{searchID, "", ""});

    if (lower != list2.end() && lower->id == searchID) {
        std::cout << "Control with ID " << searchID << " found using lower_bound:\n"
                  << "Type: " << lower->type << ", State: " << lower->state << "\n\n";
    } else {
        std::cout << "Control with ID " << searchID << " not found using lower_bound.\n\n";
    }

    if (upper != list2.end()) {
        std::cout << "First control after ID " << searchID << " using upper_bound:\n"
                  << "ID: " << upper->id << ", Type: " << upper->type 
                  << ", State: " << upper->state << "\n\n";
    } else {
        std::cout << "No controls found after ID " << searchID << " using upper_bound.\n\n";
    }

    // Step 3: Merging
    std::vector<Control> mergedList;
    std::merge(list1.begin(), list1.end(), list2.begin(), list2.end(), std::back_inserter(mergedList));
    printControls(mergedList, "Merged list of controls:");

    // Use std::inplace_merge to combine two segments in the same list
    std::vector<Control> inplaceList = list1;
    inplaceList.insert(inplaceList.end(), list2.begin(), list2.end());
    std::inplace_merge(inplaceList.begin(), inplaceList.begin() + list1.size(), inplaceList.end());
    printControls(inplaceList, "List after inplace_merge:");

    // Step 4: Set Operations
    std::vector<Control> unionList, intersectionList;

    std::set_union(list1.begin(), list1.end(), list2.begin(), list2.end(), std::back_inserter(unionList));
    printControls(unionList, "Set union (all unique controls):");

    std::set_intersection(list1.begin(), list1.end(), list2.begin(), list2.end(), std::back_inserter(intersectionList));
    printControls(intersectionList, "Set intersection (common controls):");

    return 0;
}
