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



lineas* cargarmapa(string archivo,int* num){
	int n;
	fstream rutas;
	rutas.open("1m.txt", fstream::in);
	cout<<"se abrio archivo"<<endl;
	rutas >> n;
	cout<<n<<endl;
	*num=n;
	lineas* ruta = new lineas[n];

	for(int i=0;i<n;i++){
		rutas >> (*(ruta+i)).ini.x;
		rutas >> (*(ruta+i)).ini.y;
		rutas >> (*(ruta+i)).fin.x;
		rutas >> (*(ruta+i)).fin.y;
		rutas >> (*(ruta+i)).progreso;
		rutas >> (*(ruta+i)).lins;
		rutas >> (*(ruta+i)).lina;
		rutas >> (*(ruta+i)).cond;
	}
	cout<<endl;

	for(int i=0;i<n;i++){
		cout <<"inicia: "<< (*(ruta+i)).ini.x <<','<<(*(ruta+i)).ini.y<<endl;
		cout <<"termina: "<< (*(ruta+i)).fin.x<< "," << (*(ruta+i)).fin.y<< endl;
		cout <<"vel: "<< (*(ruta+i)).progreso<< endl;
		cout <<"sig: "<< (*(ruta+i)).lins<< endl;
		cout <<"anterior: "<< (*(ruta+i)).lina<< endl;
		cout <<"cond: "<< (*(ruta+i)).cond << endl<<endl;
	}

	rutas.close();
	return ruta;
}


void ctuberias(int linact, int (&direcion)[4]){
	//dicionario para lineas actuales
	int dic[9]={0,1,0,3,1,5,2,7,3};
	int arr[4][4]={1,0,0,-1,0,1,-1,0,1,0,-1,0,0,1,0,-1};
	cout<<"mover llave"<<endl;
	for(int i=0;i<4;i++){
		cout<<direcion[i]<<" ";
	}
	cout<<endl;
	

	while(1){
		if(key[KEY_D]){
			for(int i=0;i<4;i++){
				*(direcion+i)+=arr[dic[linact]][i];
				cout<<direcion[i]<<" ";
			}
			cout<<"derecha"<<endl;
			break;
		}

		if(key[KEY_A]){
			for(int i=0;i<4;i++){
				*(direcion+i)-=arr[dic[linact]][i];
				cout<<direcion[i]<<" ";
			}
			cout<<"izquierda"<<endl;
			break;
		}
	}
}



bool jugarnivel1(){
	string archivo="1m.txt";
	int * n=new int;
	*n =5;
	cout<<*n<<endl;
	lineas* ruta = cargarmapa(archivo, n);
	cout<<"se cargo en mapa"<<endl;
	//cargaresp("1E.txt",)
	float progreso=1;
	int lineact=0;
	int colesp = makecol(255,94,0);
	int colcamino = makecol(51,153,51);
	int coljugador = makecol(255,255,0);
	BITMAP *pantalla = create_bitmap(640,480);
	BITMAP *tuberia = create_bitmap(20,80);
	line(tuberia,10,20,10,60,colcamino);
	circle(tuberia,10,60,7,coljugador);
	clear_bitmap(pantalla);
	
	for(int i=0;i<*n;i++)
		line(pantalla,(*(ruta+i)).ini.x,480-(*(ruta+i)).ini.y,(*(ruta+i)).fin.x,480-(*(ruta+i)).fin.y,colcamino);

	cords jugador;
	jugador.x=(int)ruta[lineact].ini.x+(ruta[lineact].fin.x-ruta[lineact].ini.x)*progreso/100 ;
	jugador.y=(int)ruta[lineact].ini.y+(ruta[lineact].fin.y-ruta[lineact].ini.y)*progreso/100 ;
	circle(pantalla,jugador.x,480-jugador.y,10,coljugador);
	blit(pantalla,screen,0,0,0,0,640,480);
	clear_bitmap(pantalla);


	int tuberias[4]={0,3,0,2};
	

	while(!key[KEY_ESC]){
		//movimiento
		readkey();
		if(key[KEY_D])
			progreso=progreso+(*(ruta+lineact)).progreso;

		if(key[KEY_A])
			progreso=progreso-ruta[lineact].progreso;

		if(ruta[lineact].cond==1 && key[KEY_W])
			ctuberias(lineact,tuberias);


		if(progreso>=100){
			progreso=1;
			lineact=ruta[lineact].lins;
		}

		if(progreso<=0){
			progreso=99;
			lineact=ruta[lineact].lina;
		}

		//imprimir y weas 
		for(int i=0;i<4;i++){
			rotate_sprite(pantalla,tuberia,100+150*i,150,itofix(tuberias[i]*64));
		}

		for(int i=0;i<*n;i++){
			if ((*(ruta+i)).cond)
				line(pantalla,(*(ruta+i)).ini.x,480-(*(ruta+i)).ini.y,(*(ruta+i)).fin.x,480-(*(ruta+i)).fin.y,colesp);
			else
				line(pantalla,(*(ruta+i)).ini.x,480-(*(ruta+i)).ini.y,(*(ruta+i)).fin.x,480-(*(ruta+i)).fin.y,colcamino);
		}
		
		jugador.x=(int)ruta[lineact].ini.x+(ruta[lineact].fin.x-ruta[lineact].ini.x)*progreso/100 ;
		jugador.y=(int)ruta[lineact].ini.y+(ruta[lineact].fin.y-ruta[lineact].ini.y)*progreso/100 ;
		circle(pantalla,jugador.x,480-jugador.y,10,coljugador);
		blit(pantalla,screen,0,0,0,0,640,480);
		clear_bitmap(pantalla);
	}
	return 0;
}


int main (){
	//cargar el mapa
	allegro_init();
	set_window_title("Hello World");
	install_keyboard();
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	
	jugarnivel1();
	allegro_exit();
}END_OF_MAIN()