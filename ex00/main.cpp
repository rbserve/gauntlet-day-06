#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// requires v sorted ascending; returns the index of target, or -1
int binarySearch(const std::vector<int>& v, int target){
    int lo = 0, hi = static_cast<int>(v.size());   // window = whole vector, [lo, hi)
    while (lo < hi -1) {                               // loop while window non-empty
        int mid = lo + (hi - lo) / 2;               // not (lo+hi)/2, since that sum can overflow int
        // three cases: v[mid] hits, target is right of mid, target is left of mid.
        // You write these (ex00): which bound moves, and does mid stay in the
        // window? Remember hi is exclusive: keep mid on the wrong side and
        // the window never shrinks, so the loop runs forever.
        if (target > v[mid]){
            lo = mid;
        }else if (target < v[mid]){
            hi = mid;
        }else{
            return mid;
        }
    }
    return -1;                                      // window emptied without a hit


};

int main(int argc, char* argv[]){
    std::vector<int> inputVector;

    //parsing number from argv, and populate the inputVector
    for (int i = 2; i<argc; i++ ){
        inputVector.push_back(std::stoi(argv[i]));
    }

    //sort the input vector using std::sort
    std::sort(inputVector.begin(), inputVector.end());

    //print ascending list
    std::cout << "sorted asc: ";
    for (int a : inputVector){
            std::cout << a << " ";
    }
    std::cout << std::endl;
    
    //sort the input vector using lambda comparator
    std::sort(inputVector.begin(), inputVector.end(), [](int a, int b){
        return a > b;
    });

    //print descending list
    std::cout << "sorted desc: ";
    for (int a : inputVector){
            std::cout << a << " ";
    }
    std::cout << std::endl;

    //re-sort the list
    std::sort(inputVector.begin(), inputVector.end());

    //binary search
    //get target value at argv[1], argv[0] is the program name
    const int foundIndex =  binarySearch(inputVector, std::stoi(argv[1]));

    std::string result = "";
    if (foundIndex == -1){
        result += "-1";
    }else{
        result += "index " + std::to_string(foundIndex);
    }

    std::cout << "find " <<  argv[1] << " -> " << result << std::endl;
    
    return 0;
};

