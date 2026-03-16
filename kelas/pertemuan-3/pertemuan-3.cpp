#include <iostream>
using namespace std;

// Fungsi ditaruh sebelum main
int kuadrat(int x) {
return x * x;
}

// Prosedur ditulis sebelum main
void sapa(string nama) {
cout << "Halo, " << nama << "!" << endl;
}

int main() {
sapa("Budi");
cout << "Hasil 5 kuadrat: " << kuadrat(5) << endl;
return 0;
}