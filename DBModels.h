#include <vcl.h>

#ifndef DB_MODELS_W
#define DB_MODELS_W



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
	int factory_id;
	String factory_str;

		Reciever(String name, long id, int needs, int factory_id, String factory_str){
		this->name = name;
		this->id = id;
		this->needs = needs;
		this->factory_id = factory_id;
		this->factory_str = factory_str;
	}

		Reciever(int factory_id, String factory_str){
		this->factory_id = factory_id;
		this->factory_str = factory_str;
		}

};

class ReportSummary {
	public:
	int id;
	int provider_id;
	int reciever_id;
	int value;
	int id_region_provider;
	int id_region_reciever;

	int id_factory_provider;
	int id_factory_reciever;

	String region_reciever;
	String station_reciever;

	String region_provider;
	String station_provider;

	String factory_provider;
	String factory_reciever;


	double cost;
	double total;

	int was_value;
	int dif;

		ReportSummary(int id, int provider_id, int reciever_id, int value, int id_region_provider, String region_provider,
		int id_region_reciever,
		String region_reciever, String station_reciever,   String station_provider,
		int id_factory_provider,	int id_factory_reciever, String factory_provider, String factory_reciever,
		double cost,
		double total, int was_value, int dif){

		this->id = id;
		this->provider_id = provider_id;
		this->reciever_id = reciever_id;
		this->value = value;
		this->id_region_provider = id_region_provider;
		this->id_region_reciever = id_region_reciever;

		this->region_reciever = region_reciever;
		this->station_reciever = station_reciever;

		this->region_provider = region_provider;
		this->station_provider = station_provider;

		this->cost = cost;
		this->total = total;

		this->was_value = was_value;
		this->dif = dif;

		this->id_factory_provider = id_factory_provider;
		this->id_factory_reciever = id_factory_reciever;

		this->factory_provider = factory_provider;
		this->factory_reciever = factory_reciever;

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
	long providerId;
	long recieverId;
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


		Result(	String providerName, long providerId, String recieverName, long recieverId, double cost, int value){

		this->providerName = providerName;
		this->recieverName = recieverName;
		this->providerId = providerId;
		this->recieverId = recieverId;
		this->cost = cost;
		this->value = value;
		this->itog = this->cost*this->value ;

	}


	void save(TFD){


	}
};

#endif
