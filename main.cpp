#include <iostream>
#include <fstream>
#include <allegro.h>
using namespace std;

struct cords{
	int x;
	int y;
};

struct lineas{
	cords ini;
	cords fin;
	float progreso;
	int lins;
	int lina;
	int cond;
};




int main (){
	//cargar el mapa
	allegro_init();
	set_window_title("Hello World");
	install_keyboard();
	
	float progreso=1;
	int lineact=0;
	int n;
	fstream rutas;
	rutas.open("rutas.txt", fstream::in);
	rutas >> n;
	cout<<n<<endl;
	lineas ruta[n];

	while(rutas.eof()){
		string temp;
		rutas>>temp;
		cout<<temp<<endl;
	}




	for(int i=0;i<n;i++){
		rutas >> ruta[i].ini.x;
		rutas >> ruta[i].ini.y;
		rutas >> ruta[i].fin.x;
		rutas >> ruta[i].fin.y;
		rutas >> ruta[i].progreso;
		rutas >> ruta[i].lins;
		rutas >> ruta[i].lina;
		rutas >> ruta[i].cond;
		cout<<i<<endl;
	}
	cout<<endl;
	for(int i=0;i<n;i++){
		cout <<"inicia: "<< ruta[i].ini.x <<','<<ruta[i].ini.y<<endl;
		cout <<"termina: "<< ruta[i].fin.x<< "," << ruta[i].fin.y<< endl;
		cout <<"vel: "<< ruta[i].progreso<< endl;
		cout <<"sig: "<< ruta[i].lins<< endl;
		cout <<"anterior: "<< ruta[i].lina<< endl;
		cout <<"cond: "<< ruta[i].cond << endl<<endl;
	}

	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

	while(!key[KEY_ESC]){
		//movimiento
		readkey();
		if(key[KEY_D]){
			progreso=progreso+ruta[lineact].progreso;
			cout<<lineact<<" "<<progreso<<endl;
		}
		
		if(key[KEY_A]){
			progreso=progreso-ruta[lineact].progreso;
			cout<<lineact<<" "<< progreso <<endl;
		}
		if(ruta[lineact].cond==1 && !key[KEY_W]){
			lineact++;
			progreso=1;
		}

		if(progreso>=100){
			progreso=1;
			lineact=ruta[lineact].lins;
		}
		if(progreso<=0){
			progreso=99;
			lineact=ruta[lineact].lina;
		}
	}
	allegro_exit();
}END_OF_MAIN()