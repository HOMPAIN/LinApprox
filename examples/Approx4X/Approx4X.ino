// пример аппроксимации для линейного уравнения с четыремя коэффицентами
#include "LinApprox.h"

void setup() {
  Serial.begin(115200);

  // объект аппроксимации на для уравнений вида y = a*x1+b*x2+c*x3+d*x4
  LinApprox4 approx4;
    
  // Добавляем точки (не менее 4х)
  approx4.Add(100,  10, 12,  22, 1); // 100 = a*10 + b*12 + c*22 + d
  approx4.Add(120,  30, 12,  62, 1);
  approx4.Add(1000, 10, 1002,22, 1);
  approx4.Add(1200, 40, 1001,72, 1);
  approx4.Add(1250, 40, 1031,72, 1);
    
  // вычисляем коэффиценты аппроксимации
  double a, b, c, d;
  approx4.Calc(a, b, c, d);
    
  //тестовый вывод
  Serial.print("a ");Serial.println(a);
  Serial.print("b ");Serial.println(b);
  Serial.print("c ");Serial.println(c);
  Serial.print("d ");Serial.println(d);
    
  //проверка  
  double y1= a*10+b*12+c*22+d*1;
  double y2= a*30+b*12+c*62+d*1;
  double y3= a*10+b*1002+c*22+d*1;
  double y4= a*40+b*1001+c*72+d*1;
    
  Serial.print("y1 ");Serial.println(y1);
  Serial.print("y2 ");Serial.println(y2);
  Serial.print("y3 ");Serial.println(y3);
  Serial.print("y4 ");Serial.println(y4);
}

void loop()
{
}