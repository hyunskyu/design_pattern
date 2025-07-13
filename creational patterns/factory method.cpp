#include <iostream>

class Product{ // 순수 가상 함수가 있기 때문에 추상 클래스
    public:
        virtual ~Product(){}; // 가상 소멸자
        virtual std::string Operation() const = 0 ; // 순수 가상 함수
};

class ConcreteProduct1 : public Product{
    public:
        std::string Operation() const override{
            return "{Result of the Concreteproduct1}";
        }
};

class ConcreteProduct2 : public Product{ // Product class상속
    public:
    /*
    1. const 멤버 변수 수정 안함
    2. 순수 가상 함수 override 명시
    */
        std::string Operation() const override{ 
            return "{Result of the Concreteproduct2}";
        }
};


class Creator{
    public:
        virtual ~Creator(){};
        virtual Product* FactoryMethod() const = 0; // Product 타입 factory method (상속 받을 애들이 구체적으로 어떻게 동작할건지 정해짐)

        std::string SomeOperation() const{
            Product* product = this->FactoryMethod(); 

            std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
            delete product;
            return result;

        }
};

class ConcreteCreator1 : public Creator{
    public:
        Product* FactoryMethod() const override{
            return new ConcreteProduct1();
        }
};

class ConcreteCreator2 : public Creator{
    public:
        Product* FactoryMethod() const override{
            return new ConcreteProduct2();
        }
};

void ClientCode(const Creator& creator){
    std::cout<<"Client: I'm not aware of the creator's class, but it still works\n"
            << creator.SomeOperation()<<std::endl;
}

int main(){
    std::cout<<"App: Launched with the ConcreteCreator1. \n";
    Creator* creator = new ConcreteCreator1();
    ClientCode(*creator);
    std::cout<<std::endl;
    std::cout<<"App: Launched with the ConcreteCreator2. \n";
    Creator* creator2 = new ConcreteCreator2();
    ClientCode(*creator2);
    
    delete creator;
    delete creator2;
    return 0;
}