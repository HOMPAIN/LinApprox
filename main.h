// пример для проверки
#include "LinApprox.h"
#include "iostream"
using namespace std;

int main() {
    // === 4 переменные ===
    LinApprox4 approx4;
    
    // Добавляем точки (не менее 4х)
    approx4.Add(100,  10, 12,  22, 1);
    approx4.Add(120,  30, 12,  62, 1);
    approx4.Add(1000, 10, 1002,22, 1);
    approx4.Add(1200, 40, 1001,72, 1);
    approx4.Add(1250, 40, 1031,72, 1);
    
    double a, b, c, d;
    approx4.Calc(a, b, c, d);
    
    //тестовый вывод
    cout << "a " << a << endl<< "b " << b << endl<< "c " << c << endl<< "d " << d << endl;
    
    //проверка  
    double y1= a*10+b*12+c*22+d*1;
    double y2= a*30+b*12+c*62+d*1;
    double y3= a*10+b*1002+c*22+d*1;
    double y4= a*40+b*1001+c*72+d*1;
    
    cout << endl<< "y1 " << y1 << endl<< "y2 " << y2 << endl<< "y3 " << y3 << endl<< "y4 " << y4 << endl;
    
    return 0;
}
