#include <iostream>
#include <iostream>

using namespace std;

class Singleton
{
	private : static Singleton *Instance;
	public : int x;
	
	private : Singleton() {
		cout << "Singleton()" << endl;
		x = 55;
	}
	
	public : static Singleton* getInstance() {
		if(Instance == NULL)
		{
			Instance = new Singleton();
		}
		return Instance;
	}
	
	void method() {
		x++;
	}
};

Singleton* Singleton::Instance = NULL;

int main()
{
	Singleton *Ins1 = Singleton::getInstance();
	cout << "Ins1->x : " << Ins1->x << endl;
	Singleton *Ins2 = Singleton::getInstance();
	Ins2->method();
	
	cout << "Ins1->x : " << Ins1->x << endl;
	
	return 0;
}
