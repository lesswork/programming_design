#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>

enum state
{
	created = 0,
	modified,
	deleted,
};

using namespace std;

class IInterface
{
protected:
	int event;
public:
	IInterface() { }
	virtual void created(int event) = 0;
	virtual void modified(int event) = 0;
	virtual void deleted(int event) = 0;
};

class Observer
{
private:
	vector<IInterface*> medium;
	int event;

    pthread_t thread;
    pthread_attr_t attr;
    void* status;
    int thread_id;

public:
	void Register(IInterface* p)
	{
		medium.push_back(p);
	}
	int unRegister(IInterface* p)
	{
		vector<IInterface *>::iterator it;
		for(it = medium.begin() ; it != medium.end() ; ++it)
		{
				if(*it == p)
				{
					cout << "UnRegister" << endl;
					medium.erase(it);
					return 0;
				}
		}
		return -1;
	}
	// Will call Notify when change done
	void Change(int p)
	{
		event = p;
		if(event == created)
			Notify_created();
		else if(event == modified)
			Notify_modified();
		else if(event == deleted)
			Notify_deleted();
	}

	// Called event changed
	// can check for some condition and then call Update funtions also.
	void Notify_created()
	{
		for(vector<IInterface*>::iterator it = medium.begin() ; 
			it != medium.end() ; ++it )
			(*it)->created(event);
	}
	void Notify_modified()
	{
		for(vector<IInterface*>::iterator it = medium.begin() ; 
			it != medium.end() ; ++it )
			(*it)->modified(event);
	}
	void Notify_deleted()
	{
		for(vector<IInterface*>::iterator it = medium.begin() ; 
			it != medium.end() ; ++it )
			(*it)->deleted(event);
	}

	int CreateThread();
	static void *threadFunction(void *);
};

int Observer::CreateThread()
{
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	cout << "Observer::CreateThread creating thread now" << endl;
	int rc = pthread_create(&thread, &attr, threadFunction, (void *)this);

	if (rc) {
		cerr << "ERROR; return code from pthread_create() is : " << rc << endl;
		return -1;
	}

	pthread_attr_destroy(&attr);

	rc = pthread_join(thread, &status);

	if (rc) {
		cerr << "ERROR; return code from pthread_join() is : " <<  rc << endl;
		return -1;
	}
	cout << "Thread Joined" <<  endl;
}

void *Observer::threadFunction(void *t)
{
	cout << "threadFunction() called" << endl;
}

class Bluetooth : public IInterface
{
	virtual void created(int i)
	{
		cout << "Bluetooth() created" << endl;
		event =i;
	}
	virtual void modified(int i)
	{
		cout << "Bluetooth() modified" << endl;
		event =i;
	}
	virtual void deleted(int i)
	{
		cout << "Bluetooth() deleted" << endl;
		event =i;
	}
};

class Wifi : public IInterface
{
	virtual void created(int i)
	{
		cout << "Wifi() created" << endl;
		event =i;
	}
	virtual void modified(int i)
	{
		cout << "Wifi() modified" << endl;
		event =i;
	}
	virtual void deleted(int i)
	{
		cout << "Wifi() deleted" << endl;
		event =i;
	}
};

int main()
{
	Observer bob;
	bob.CreateThread();
	cout << endl;

	Bluetooth b1;
	Wifi w1;
	Bluetooth b2;

	bob.Register(&b1);
	bob.Register(&w1);
	bob.Register(&b2);
	
	// Notify all IInterface, call Update()
	bob.Change(created);
	cout << endl;
	bob.Change(modified);
	cout << endl;
	bob.Change(deleted);
	cout << endl;

	if(bob.unRegister(&b2) == -1)
	{
		cerr << "Object is not registered" << endl;
	}

	bob.Change(modified);
	cout << endl;
	return 0;
}
