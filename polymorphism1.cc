#include <iostream>
#include <string.h>

using namespace std;

class MediumInterface
{
	public:
		MediumInterface()
		{
			cout << "cttor : MediumInterface()" << endl;
		}
		//virtual int transmit() {cout << "transmit()" << endl;} //= 0;
		//virtual int receive() {cout << "receive()" << endl;} //= 0;
		
		virtual int transmit() = 0;
		virtual int receive() = 0;
		~MediumInterface()
		{
			cout << "~dttor : MediumInterface()" << endl;
		}
};

class UARTInterface : public MediumInterface
{
	private:
		int data;
	public:
		UARTInterface()
		{
			cout << "cttor : UARTInterface()" << endl;
		}
		int transmit()
		{
			cout << "Sending data via UART" << endl;
			return 0;
		}
		int receive()
		{
			cout << "Receiving data via UART" << endl;
			return 0;
		}
		~UARTInterface()
		{
			cout << "~dttor : UARTInterface()" << endl;
		}
};

class SPIInterface : public MediumInterface
{
	private:
		int data;
	public:
		SPIInterface()
		{
			cout << "cttor : SPIInterface()" << endl;
		}
		int transmit()
		{
			cout << "Sending data via SPI" << endl;
			return 0;
		}
		int receive()
		{
			cout << "Receiving data via SPI" << endl;
			return 0;
		}
		~SPIInterface()
		{
			cout << "~dttor : SPIInterface()" << endl;
		}
};

template <typename T>
class Factory
{
	public :
	MediumInterface* createInterface()
	{
		cout << "createInterface()" << endl;
		return new T();
	}
};

int main(void)
{
	Factory<UARTInterface> factory;
	MediumInterface* stream = factory.createInterface();
	stream->transmit();
	stream->receive();

	return 0;
}
