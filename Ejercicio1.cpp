// g++ -std=c++17 carrito_min.cpp -o carrito && ./carrito
#include <bits/stdc++.h>
using namespace std;

struct Producto{ string nombre; double precio; int stock; };
struct ItemCarrito{ Producto* p; int c; double sub()const{return c*p->precio;} };
struct Compra{ string fecha; double total; vector<pair<string,int>> items; };
struct Usuario{
    string nombre; vector<Compra> historial;
    void ver()const{
        if(historial.empty()){ cout<<"\n(no hay compras)\n"; return; }
        cout<<"\n=== Historial de "<<nombre<<" =\n"<<fixed<<setprecision(2);
        for(size_t i=0;i<historial.size();++i){ auto& k=historial[i];
            cout<<i+1<<") "<<k.fecha<<" | Total $"<<k.total<<"\n";
            for(auto& it:k.items) cout<<"   - "<<it.first<<" x"<<it.second<<"\n";
        }
    }
};

struct Carrito{
    vector<ItemCarrito> v;
    static string ahora(){ time_t t=time(nullptr); char b[20]; strftime(b,20,"%Y-%m-%d %H:%M",localtime(&t)); return b; }
    bool agregar(Producto& p,int c){ if(c<=0||p.stock<c) return false; p.stock-=c;
        for(auto& it:v) if(it.p==&p){ it.c+=c; return true; } v.push_back({&p,c}); return true; }
    bool quitar(int i){ if(i<0||i>=(int)v.size()) return false; v[i].p->stock+=v[i].c; v.erase(v.begin()+i); return true; }
    double total()const{ double t=0; for(auto& it:v) t+=it.sub(); return t; }
    void ver()const{
        cout<<"\n=== Carrito ===\n"; if(v.empty()){ cout<<"(vacío)\n"; return; }
        cout<<fixed<<setprecision(2);
        for(size_t i=0;i<v.size();++i) cout<<i<<") "<<v[i].p->nombre<<" x"<<v[i].c<<" | $"<<v[i].p->precio<<" | Sub $"<<v[i].sub()<<"\n";
        cout<<"Total: $"<<total()<<"\n";
    }
    bool pagar(Usuario& u){
        if(v.empty()) return false;
        Compra c; c.fecha=ahora(); c.total=total();
        for(auto& it:v) c.items.push_back({it.p->nombre,it.c});
        u.historial.push_back(move(c)); v.clear(); cout<<"Compra realizada.\n"; return true;
    }
};

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);

    vector<Producto> inv = {
        {"Manzanas",2.5,20},{"Queso",15.9,10},{"Vino",45,5},{"Chocolate",7.25,12}
    };
    auto listar=[&]{ cout<<"\n=Inventari =\n"<<fixed<<setprecision(2);
        for(size_t i=0;i<inv.size();++i) cout<<i<<") "<<inv[i].nombre<<" | $"<<inv[i].precio<<" | stock "<<inv[i].stock<<"\n"; };

    Usuario u{"Estudiante"}; Carrito c; int op;
    while(true){
        cout<<"\n1 Inventario  2 Agregar  3 Carrito  4 Quitar  5 Total  6 Pagar  7 Historial  0 Salir\n> ";
        if(!(cin>>op)) break; if(op==0) break;
        if(op==1) listar();
        else if(op==2){ listar(); int i,q; cout<<"idx cant: "; cin>>i>>q;
            if(i>=0&&i<(int)inv.size()&&!c.agregar(inv[i],q)) cout<<"Stock insuficiente.\n"; }
        else if(op==3) c.ver();
        else if(op==4){ int i; cout<<"idx en carrito: "; cin>>i; if(!c.quitar(i)) cout<<"Índice inválido.\n"; }
        else if(op==5) cout<<fixed<<setprecision(2)<<"Total: $"<<c.total()<<"\n";
        else if(op==6) c.pagar(u);
        else if(op==7) u.ver();
    }
    cout<<"Adiós!\n";
}
