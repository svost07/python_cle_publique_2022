//Import necessary packages 
#include <pybind11/pybind11.h>
#include "micro-ecc/uECC.h"

class Cle
{   
    private:
        char * private_k;
        char * public_k;
    public:
        Cle() { this->private_k = (char*) malloc(64*sizeof(char));
                this->public_k = (char*) malloc(2*64*sizeof(char));
                }
        ~Cle() { 
            free(this->private_k); 
            free(this->public_k);}

        void initialize(char* key) {
            for(int i=0;i<64;i++){
                this->private_k[i] = key[i];
            }
        }
        char* getPrivateKey() { 
            return this->private_k;
        }
	
	//Get public key using a function from ECC
        char* getPublicKey() {
            uECC_make_key((uint8_t *)this->public_k, (uint8_t *) this->private_k, uECC_secp256k1());
            return this->public_k;
         }

};

//Conversion to python class
namespace py = pybind11;
PYBIND11_MODULE(composant_cle, greetings)
{
  
   // bindings to cle composant class
    py::class_<Cle>(greetings, "Cle")
        .def(py::init<>())
        .def("initialize", &Cle::initialize)
        .def("getPrivateKey", &Cle::getPrivateKey)
        .def("getPublicKey", &Cle::getPublicKey);
}
