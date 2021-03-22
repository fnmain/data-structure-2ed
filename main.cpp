#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main()
{
    set<int> s;
    s.insert(1);

    cout << *(s.begin()) << endl;
    
    return 0;
}