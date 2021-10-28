# include <iostream>
# include <cmath>
# include <vector> 
using namespace std;

class Bateria{
    public:
    Bateria(int mah, int tempoDeCarregamento){
        this->mah=mah;
        this->tempoDeCarregamento=tempoDeCarregamento;
        carga = 0;
        uso = false;
        carregavel = true;
    }
    bool carregar(int tempo){
        if(carga < mah){
            carga  += mah*(tempo/tempoDeCarregamento);
            return true;
        }
        return false;
    }
    bool usar(int tempo){
        carga -= mah*(tempo/tempoDeCarregamento);
        if(carga != 0){return true;}
        return false;
    }

    int calculaTempoDeVoo(){
        return (carga*tempoDeCarregamento)/mah;
    }
    int getCarga(){
        return carga;
    }
    int getTempoDeCarregamento(){
        return tempoDeCarregamento;
    }
    int getmah(){
        return mah;
    }
    bool getUso(){
        return uso;
    }
    bool getCarregavel(){
        return carregavel;
    }
    void setUso(bool uso){ 
        this->uso = uso;
    }
    void setCarregavel(bool carregavel){
        this->carregavel = carregavel;
    }
    void status(){
        if(uso == true && carregavel == true){
            cout << "Bateria com capacidade" << mah << "e tempo de carregamento" << tempoDeCarregamento << endl << "Com carga atual: " << carga << endl << "Tempo de voo disponivel: " << (carga*tempoDeCarregamento)/mah << endl << "Esta sendo usada: sim" << endl << "Pode ser carregada no momento: sim";    
        }
        else if(uso == true && carregavel == false){
            cout << "Bateria com capacidade" << mah << "e tempo de carregamento" << tempoDeCarregamento << endl << "Com carga atual: " << carga << endl << "Tempo de voo disponivel: " << (carga*tempoDeCarregamento)/mah << endl << "Esta sendo usada: sim" << endl << "Pode ser carregada no momento: nao";}
        else if(uso == false && carregavel == true){
            cout << "Bateria com capacidade" << mah << "e tempo de carregamento" << tempoDeCarregamento << endl << "Com carga atual: " << carga << endl << "Tempo de voo disponivel: " << (carga*tempoDeCarregamento)/mah << endl << "Esta sendo usada: nao" << endl << "Pode ser carregada no momento: sim";}
        else{cout << "Bateria com capacidade" << mah << "e tempo de carregamento" << tempoDeCarregamento << endl << "Com carga atual: " << carga << endl << "Tempo de voo disponivel: " << (carga*tempoDeCarregamento)/mah << endl << "Esta sendo usada: nao" << endl << "Pode ser carregada no momento: nao";}
    }
    private;
    int mah;
    int tempoDeCarregamento;
    int carga; 
    bool uso;
    bool carregavel;
}

class Drone{
    public:
    Drone(string nome, Bateria* bateria, double posicao){
        this->nome = nome;
        this->posicao = posicao;
        altura = 0.0;
        decolado = false;
    }
    bool takeoff(double altura){
        decolado = true;
        bateria.setCarregavel(false);
        if(bateria->usar(altura/60)==false){
            return false;}
        else{
            this->altura = altura;
            return true;}
    }
    bool setPosition(double x, double y){
        if(decolado == false){
            cout << "Drone nao foi decolado. Nao e possivel mudar sua posicao" << endl;
            return false;}
        else if(x<0.0 || y<0.0){
            return false;
        }
        else if(bateria->usar(sqrt(pow((x-posicao),2)+pow((y-altura),2))/60)==true){
            posicao = x;
            altura = y;
            return true;
        }
        else{return false;}
    }
    double getPosicao(){
        return posicao;
    }
    double getAltura(){
        return altura;
    }
    void land(){
        altura = 0.0;
        decolado = false;
        bateria.setCarregavel(true);
    }
    virtual bool mapear(){
        if(nome=="S1000"){
            return true;
        }
        return false;
    }
    void status(){
        cout << "Drone" << nome << endl << "Bateria com" << bateria.getCarga() << mAh << endl << "Drone esta na posicao (" << x << "," << y << ")" << endl;
    }
    private:
    string nome;
    double posicao, altura;
    bool decolado;
}

class S1000: public Drone{
    public:
    bool mapear(){
        if(bateria.calculaTempoDeVoo()<10){
            return false;
        }
        else{
            cout << "Mapeando..."<< endl << "__________________(oooo)__" << endl << "__o-o_____\0/_______||____" << endl << "___________|________||____" << endl << "___________/\_______||____" << endl << "__________________________" << endl << "Mapeamento feito!" << endl;
            return true;
        }
    }
}

void main(){
    string nome;
    int opcao, opcao1, mah, tempoDeCarregamento, posicao, *bat, *drone, tempo;
    double posicao, altura, x, y; 
    opcao = 0;
    while(opcao<8){
        cout << "1. Comprar bateria " << endl << "2. Comprar um S1000 " << endl << "3. Montar um drone generico" << endl << "4. Usar os drones existentes" << endl << "5. Carregar  baterias disponiveis" << endl << "6. Listar drones existentes" << endl << "7. Listar baterias existentes" << endl << "8. Sair" << endl;
        cin >> opcao;
        if(opcao==1){
            cout << "Digite mah" << endl;
            cin >> mah;
            cout << "Digite o tempo de carregamento" << endl;
            cin >> tempoDeCarregamento;
            Bateria* bateria = new Bateria(mah, tempoDeCarregamento);
            vector<Bateria*> *baterias = new vector<Bateria*>();
            baterias->push_back(bateria);
        }
        else if(opcao==2){
            cout << "Digite a posicao horizontal do drone" << endl;
            cin >> posicao;
            Bateria* bateria = new Bateria(22000,40);
            Drone *S1000 = new S1000(S1000, Bateria* bateria, posicao);
            vector<Drone*> *drones = new vector<Drone*>();
            drones->push_back(S1000);
        }  
        else if(opcao==3){
            cout << "Digite o nome do drone " << endl;
            cin >> nome;
            cout << "Digite a posição horizontal do drone" << endl;
            cin >> posicao;
            cout << "Digite qual bateria deseja utilizar" << endl;
            cin >> Bateria *bat;
            baterias->pop_back(Bateria *bat);
            Drone *drone = new drone(nome, Bateria* bat, posicao);
            drones->push_back(drone);
        }
        else if(opcao==4){
            cout << "Qual drone deseja usar? " << endl;
            cin >> Drone *drone;
            opcao1 = 0;
            while(opcao1<5){
                cout << "1. Decolar o drone " << endl << "2. Ir para uma posicao " << endl << "3. Pousar o drone" << endl << "4. Mapear" << endl << "5. Sair";
                cin >> opcao1;
                if(opcao1==1){
                    cout << "Digite a altura para a qual deseja decolar " << endl;
                    cin >> altura;
                    if(drone.takeoff(altura)==true){
                        cout << "Drone decolado com sucesso para altura" << altura << endl;
                    }
                    else{
                        cout << "Drone nao tem bateria suficiente para se movimentar " << endl;
                    }
                }
                else if(opcao1==2){
                    cout << "Digite a posicao horizontal para onde quer ir" << endl;
                    cin >> x;
                    cout << "Digite a altura para onde quer ir" << endl;
                    cin >> y;
                    if(drone.setPosition(x,y)==true){
                        cout << "Drone foi movido com sucesso para a posicao (" << x << "," << y << ")" << endl;
                    }
                    else{
                        cout << "Nao foi possivel pousar o drone" << endl;
                    }
                }
                else if(opcao1 == 3){
                    drone.land();
                    cout << "Drone pousado com sucesso";
                }
                else if(opcao1 == 4){
                    if(drone.mapear()==false){
                        cout << "Esse drone nao faz maepamento!" << endl;
                    }
                    else if(S1000.mapear()==false){
                        cout << "S1000 tem que ficar no mínimo 10 minutos para poder mapear!" <<endl;
                    }
                    else{
                        S1000.mapear()
                    }
                }
            }
            cout << "Voce saiu da interface" << endl;  
        }
        else if(opcao1==5){
            cout << "Por quanto tempo vc quer deixar as baterias carregando? "<< endl;
            cin>>tempo;
            for(unsigned int i = 0; i < baterias->size(); i++){
                baterias->at(i)->bateria.carregar(tempo);
            }

        }




            
            

        }


        }

    }

}

Bateria* bateria = new Bateria();
