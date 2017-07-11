#include <iostream>
using namespace std;
short getTrueForm(const short& X){
    return X*X;
}

int main(int argc, char *argv[])
    {
         cout<<getTrueForm(6);
         return 0;
}