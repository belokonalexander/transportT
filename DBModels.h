class Provider {
    public:
	String name;
	long id;
	int reserve;

	Provider(String name, long id, int reserve){
		this->name = name;
		this->id = id;
		this->reserve = reserve;
	}

	String toString(){
        return " -> "  + name + " / " + id + " / " + reserve;
	}

};

class Reciever {
	public:
	String name;
	long id;
	int needs;

		Reciever(String name, long id, int needs){
		this->name = name;
		this->id = id;
		this->needs = needs;
	}

};

class Tarif {
	public:
	String recieverName;
	String providerName;
	double cost;

	Tarif(String providerName, String recieverName, double cost){
		this->recieverName = recieverName;
		this->providerName = providerName;
		this->cost = cost;
	}

};

class Result {
	public:
	String providerName;
	String recieverName;
	double cost;
	int value;
	double itog;

	Result(	String providerName, String recieverName, double cost, int value, double itog){

		this->providerName = providerName;
		this->recieverName = recieverName;
		this->cost = cost;
		this->value = value;
        this->itog = itog;

	}
};