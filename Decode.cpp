#include "Head.h"

int main()
{
    ifstream In("Encoded.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error";
        return 0;
    }
    ofstream Out("Decoded.txt", ios::binary);
    if (!In.is_open())
    {
        cout << "error";
    }
    Arithmetic a(10);
    a.ReadCap(In);
   // a.PrintMap();
    a.Decoded(In, Out);
    In.close();
    Out.close();
    return 0;
}
