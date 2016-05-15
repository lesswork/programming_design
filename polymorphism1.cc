#include <iostream>
#include <string.h>

using namespace std;

#define SPI_INTERFACE "SPI"
#define UART_INTERFACE "UART"

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

class Factory
{
	public :
	MediumInterface* createInterface(const char *type)
	{
		if(strcmp(type,"UART") == 0)
			return new UARTInterface();
		else if(strcmp(type,"SPI") == 0)
			return new SPIInterface();
		else
			return NULL;
	}
};

int main(void)
{
	Factory *factory;
	MediumInterface* stream =(MediumInterface *) factory->createInterface(SPI_INTERFACE);
	stream->transmit();
	
	return 0;
}
