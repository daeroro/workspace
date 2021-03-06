#include <iostream>
#include <string.h>

using namespace std;

class Car // << 클래스명
{
private:
    int speed;
    char color[32];

public:
//	Car(void);
	~Car(void);
    void setSpeed(int s);
    int getSpeed(void);
    void setColor(char *c);
    char *getColor(void);
};
// Car:: << Car라는 구조체에 있는 함수포인터를 밑에와 같이 정의하겟다는 거에요.

Car::~Car(void)
{
	cout << "Call Destructor" << endl;
}

void Car::setSpeed(int s)
{
    speed = s;
}

int Car::getSpeed(void)
{
    return speed;
}

void Car::setColor(char *c)
{
    strcpy(color, c);
}

char *Car::getColor(void)
{
    return color;
}

int main(void) 
{
   Car c = Car();
   c.setSpeed(180);
   cout << "speed = " << c.getSpeed() << endl;

   c.setColor("파랑");
   cout << "색깔 = " << c.getColor() << endl;
	return 0;
}
