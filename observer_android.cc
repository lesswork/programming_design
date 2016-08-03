#include <iostream>
#include <string>
#include <vector>

enum state
{
	created = 0,
	started,
	stoped,
	deleted,
};

using namespace std;

class Subscriber
{
protected:
	int price;
public:
	Subscriber() { }
	virtual void created(int price) = 0;
	virtual void started(int price) = 0;
	virtual void deleted(int price) = 0;
};

class StockBroker
{
private:
	vector<Subscriber*> subscriber;
	int price;
public:
	void Register(Subscriber* p)
	{
		subscriber.push_back(p);
	}

	// Will call Notify when change done
	void Change(int p)
	{
		price = p;
		if(price == created)
			Notify_created();
		else if(price == started)
			Notify_started();
		else if(price == deleted)
			Notify_deleted();
	}

	// Called hen price changed
	// can check for some condition and then call Update funtions also.
	void Notify_created()
	{
		for(vector<Subscriber*>::iterator it = subscriber.begin() ; 
			it != subscriber.end() ; ++it )
			(*it)->created(price);
	}
	void Notify_started()
	{
		for(vector<Subscriber*>::iterator it = subscriber.begin() ; 
			it != subscriber.end() ; ++it )
			(*it)->started(price);
	}
	void Notify_deleted()
	{
		for(vector<Subscriber*>::iterator it = subscriber.begin() ; 
			it != subscriber.end() ; ++it )
			(*it)->deleted(price);
	}
};

class Equity : public Subscriber
{
	virtual void created(int i)
	{
		cout << "Equity() created" << endl;
		price =i;
	}
	virtual void started(int i)
	{
		cout << "Equity() started" << endl;
		price =i;
	}
	virtual void deleted(int i)
	{
		cout << "Equity() deleted" << endl;
		price =i;
	}
};

class MutualFund : public Subscriber
{
	virtual void created(int i)
	{
		cout << "MutualFund() created" << endl;
		price =i;
	}
	virtual void started(int i)
	{
		cout << "MutualFund() started" << endl;
		price =i;
	}
	virtual void deleted(int i)
	{
		cout << "MutualFund() deleted" << endl;
		price =i;
	}
};

// create singletone method without pointer
int main()
{
	StockBroker bob;

	Equity ajay;
	MutualFund vijay;
	Equity satish;

	bob.Register(&ajay);
	bob.Register(&vijay);
	bob.Register(&satish);
	
	// Notify all subscribers, call Update()
	bob.Change(created);
	cout << endl;
	bob.Change(started);
	cout << endl;
	bob.Change(deleted);
	cout << endl;
	return 0;
}
