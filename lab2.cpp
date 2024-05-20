#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
using namespace std;
    vector<string> Jerarqui = {"^","*","/","+","-"};
    map<string , int> orD = {
          // false para asociatividad derecha
    {"*", 0},   // true para asociatividad izquierda
    {"/", 0},
    {"+", 1},
    {"-", 1},    // true para asociatividad izquierda
};

    class operations { //clase general 
    public:
        virtual double cal() const = 0; //virtual puro 
        virtual ~operations() {}  // destructor 
    };

    class number : public operations {
    private:
        double valor; //encapsular el valor numerico (mantener integridad del mismo ) 
    public:
        number(double val) : valor(val) {}

        double cal() const override { //sobreescribir en cal porque es puro 
            return valor;
        }
    };

    class sumita : public operations {
    private:
        const number* operando1;
        const number* operando2;
    public:
        sumita(const number* op1, const number* op2) : operando1(op1), operando2(op2) {}

        double cal() const override {
            return operando1->cal() + operando2->cal();
        }
    };

    class restita : public operations {
    private:
        const operations* operando1;
        const operations* operando2;
    public:
        restita(const operations* op1, const operations* op2) : operando1(op1), operando2(op2) {}

        double cal() const override {
            return operando1->cal() - operando2->cal();
        }
    };

    class multi : public operations {
    private:
        const number* operando1;
        const number* operando2;
    public:
        multi(const number* op1, const number* op2) : operando1(op1), operando2(op2) {}

        double cal() const override {
            return operando1->cal() * operando2->cal();
        }
    };
    class divi : public operations {
    private:
        const number* operando1;
        const number* operando2;
    public:
        divi(const number* op1, const number* op2) : operando1(op1), operando2(op2) {}
            double cal() const override {
                double divisor = operando2->cal();
                if (divisor == 0) {
                    throw;
                }
            return operando1->cal() / divisor;
            }
    };
    class ponte : public operations {
    private:
        const operations* operando1;
        const operations* operando2;
    public:
        ponte(const operations* op1, const operations* op2) : operando1(op1), operando2(op2) {}

        double cal() const override {
            return pow(operando1->cal(),operando2->cal());
        }
    };


    class Operador : public operations {
    private:
        char operador;
    public:
        Operador(char op) : operador(op) {}

        double cal() const override {
            return operador;
        }
    };


    int finds(string val,vector<string> vector_){
        for(int i = 0;i<vector_.size();i++){
            if(val==vector_[i]){
                return i;
            }
        }
        return -1;
    }
    int findOrd(int val,vector<string> vector_){
        for(int i = 0;i<vector_.size();i++){
            if(val==0){
                if(vector_[i] == "/" || vector_[i] == "*"  ){
                return i;
            }
            }else{
                
                return i;
            }
            
        }
        return -1;
    }
    bool find(string val,vector<string> vector_){
        for(int i = 0;i<vector_.size();i++){
            if(val==vector_[i]){
                return true;
            }
        }
        return false;
    }
    int main() {
        cout << "ingrese la operacion please " << endl;

        vector<operations*> resolver;
        double valor;
        char operador;
        string val;
        double sal;
        vector<string> operations;
        vector<double> factors;
        vector<int> order_ops;
        vector<int> position;
        //cosntruir la expresion mate
        std::vector<string>::iterator it;
        cin>>sal;
        factors.push_back(sal);
        while(cin>>val){
            if(val == "="){
                break;
            }
            if(find(val,Jerarqui)){
                operations.push_back(val);
                 
                order_ops.push_back(orD[val]);
                
            }
            cin>>sal;
            factors.push_back(sal);
        
        }
        sort(order_ops.begin(), order_ops.end());
       
        for(auto i : factors){
            cout<<i;
        }
        for(auto i : operations){
            cout<<i;
        }
        int i = 0;
        double result = 0;
        while (!operations.empty())
        {
            
            for(auto i : order_ops){
                cout<<"Order " <<i<<endl;
            }
            int x = findOrd(order_ops[i],operations);
            string actual_op = operations[x];
            cout<< "Este es " << x <<endl ; 
            number* op1 = new number(factors[x]);
            number* op2 = new number(factors[x+1]);
            if(actual_op == "+"){
                resolver.push_back(new sumita(op1,op2));
            }else if(actual_op == "*"){
                resolver.push_back(new multi(op1,op2));
            }else if(actual_op == "/"){
                resolver.push_back(new divi(op1,op2));
            }else{
                resolver.push_back(new restita(op1,op2));
            }
            
            cout<<resolver[0]->cal()<<endl;
            factors[x] = resolver[0]->cal();
            factors.erase(factors.begin()+x+1);
            operations.erase(operations.begin()+x);
            result = resolver[0]->cal();
            resolver.pop_back();
            i++;
            
            
            
        }
        
        cout<<result;    
        
            
            
            /*resolver.push_back(new number(valor));  

            
            if (operador == '*' || operador == '+' || operador == '-' || operador == '/' || operador =='^') {
                resolver.push_back(new number(operador));
            } else {
                cerr << "no existe ese operador: " << operador << endl;
                return 1;
            }*/
        

        
        
        //evaluar la expresion y resolver
/*
        double resultado = resolver[0]->cal();

try {
        for (size_t i = 1; i < resolver.size(); i += 2) {
            double op = resolver[i]->cal();
            double valor = resolver[i + 1]->cal();

            if (op == '^') {
                resultado = pow(resultado, valor);
            } else if (op == '*' || op == '/') {
                if (op == '*') {
                    resultado *= valor;
                } else {
                    if (valor == 0) {
                        throw "Error: división por cero";
                    }
                    resultado /= valor;
                }
            } else {
                if (op == '+') {
                    resultado += valor;
                } else {
                    resultado -= valor;
                }
            }
        }
            cout << "resultado: " << resultado << endl;
        } catch (const char* e) {
            cerr << "atrapado  " << e << endl;
        }

        while (!resolver.empty()) { 
        delete resolver.back(); 
        resolver.pop_back();
    }
    resolver.clear(); //elimina los residuos */
     return 0;

}

   