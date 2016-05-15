#include <iostream>

using namespace std;

class MediumInterface
{
	public:
		MediumInterface()
		{
			cout << "cttor : MediumInterface()" << endl;
		}
		virtual int transmit() {cout << "transmit()" << endl; return 0; } //= 0;
		virtual int receive() {cout << "receive()" << endl; return 0; } //= 0;
		
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

int main(void)
{
	UARTInterface UARTstream;
	SPIInterface SPIstream;

	MediumInterface *stream = &SPIstream;
	stream->transmit();
	stream = &UARTstream;
	stream->transmit();
	return 0;
}
