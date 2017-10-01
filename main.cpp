#include "clase.h"

int main()
{
    system("clear");
    int ncels, taman, met;
    
    cout << "Nº de celdas: ";
    cin >> ncels;
    cout << endl << "Tamaño del bloque: ";
    cin >> taman;
    tabla tablita(ncels,taman);
    cout << endl << "Seleccione el método de exploración (1-4): \n1) Lineal \n2)Cuadrática\n3)Dispersión doble\n4)Redispersión\n";
    cin >> met;
    
    float factor;
    int total_a_almacenar;
    
    do{
	cout << "Factor de carga: "; 
	cin >> factor;
    }while(factor > 1 || factor < 0);
    
    total_a_almacenar = factor * ncels * taman;
    cout << "Total a almacenar = " << total_a_almacenar <<endl;
    
    int nbusquedas, ninserciones, ncomparaciones = 0, maxcomparaciones = 0, mincomparaciones = 9999, compactuales;
    int j; //para controlar que no se salga de las claves insertadas al buscar
    float mediacomparaciones;
    
    cout << "Nº de búsquedas = "; 
    cin >> nbusquedas;
    
    do{
        cout << "Nº de inserciones sin alterar FC = ";
	cin >> ninserciones;
    }while(ninserciones > ncels * taman - total_a_almacenar);
    
    system("clear");
    aleatorio ale(800);

    switch(met)
    {
        case 1:
	    for(int i = 0; i < total_a_almacenar; i++)
	    {
	      tablita.in_lineal(ale.get_nelem(i),1);
	    }
	    ncomparaciones = maxcomparaciones = 0;
	    mincomparaciones = 9999;
	    for(int i = 0 ; i < nbusquedas ;i++)
	    {
		j = rand() % total_a_almacenar;
		compactuales = tablita.busq_lineal(ale.get_nelem(j));
		if(compactuales > maxcomparaciones)
		{
		    maxcomparaciones = compactuales;
		}
		if(compactuales < mincomparaciones)
		{
		    mincomparaciones = compactuales;
		}
		ncomparaciones += compactuales;
	    }
	    mediacomparaciones = (float)ncomparaciones / nbusquedas;
	    tablita.estadisticas(nbusquedas,ncomparaciones,mincomparaciones,mediacomparaciones,maxcomparaciones,2); //DATOS DE BUSQUEDA 
	    ncomparaciones = maxcomparaciones = 0; mincomparaciones = 9999;
	    for(int i = 0 ; i < ninserciones ; ++i)
	    {
	      compactuales = tablita.in_lineal(ale.get_nelem(i),0);
	      if(compactuales > maxcomparaciones)
	      {
		  maxcomparaciones = compactuales;
	      }
	      if(compactuales < mincomparaciones)
	      {
		  mincomparaciones = compactuales;
	      }
	      ncomparaciones += compactuales;
	    }
	    mediacomparaciones = (float)ncomparaciones / ninserciones;
	    tablita.estadisticas(ninserciones,ncomparaciones,mincomparaciones,mediacomparaciones,maxcomparaciones,1); //DATOS INSERCION
            break;
        case 2:
	    for(int i = 0; i < total_a_almacenar; i++)
	    {
	      tablita.in_cuadratica(ale.get_nelem(i),1);
	    }
	    ncomparaciones = maxcomparaciones = 0;
	    mincomparaciones = 9999;
	    for(int i = 0 ; i < nbusquedas ;i++)
	    {
		j = rand() % total_a_almacenar;
		compactuales = tablita.busq_cuadratica(ale.get_nelem(j));
		if(compactuales > maxcomparaciones)
		{
		    maxcomparaciones = compactuales;
		}
		if(compactuales < mincomparaciones)
		{
		    mincomparaciones = compactuales;
		}
		ncomparaciones += compactuales;
	    }
	    mediacomparaciones = (float)ncomparaciones / nbusquedas;
	    tablita.estadisticas(nbusquedas,ncomparaciones,mincomparaciones,mediacomparaciones,maxcomparaciones,2); //DATOS DE BUSQUEDA 
	    ncomparaciones = maxcomparaciones = 0; mincomparaciones = 9999;
	    for(int i = 0 ; i < ninserciones ; ++i)
	    {
	      compactuales = tablita.in_cuadratica(ale.get_nelem(i),0);
	      if(compactuales > maxcomparaciones)
	      {
		  maxcomparaciones = compactuales;
	      }
	      if(compactuales < mincomparaciones)
	      {
		  mincomparaciones = compactuales;
	      }
	      ncomparaciones += compactuales;
	    }
	    mediacomparaciones = (float)ncomparaciones / ninserciones;
	    tablita.estadisticas(ninserciones,ncomparaciones,mincomparaciones,mediacomparaciones,maxcomparaciones,1); //DATOS INSERCION
            break;
        case 3:
	    for(int i = 0; i < total_a_almacenar; i++)
	    {
	      tablita.in_doble(ale.get_nelem(i),1);
	    }
	    ncomparaciones = maxcomparaciones = 0;
	    mincomparaciones = 9999;
	    for(int i = 0 ; i < nbusquedas ;i++)
	    {
		j = rand() % total_a_almacenar;
		compactuales = tablita.busq_doble(ale.get_nelem(j));
		if(compactuales > maxcomparaciones)
		{
		    maxcomparaciones = compactuales;
		}
		if(compactuales < mincomparaciones)
		{
		    mincomparaciones = compactuales;
		}
		ncomparaciones += compactuales;
	    }
	    mediacomparaciones = (float)ncomparaciones / nbusquedas;
	    tablita.estadisticas(nbusquedas,ncomparaciones,mincomparaciones,mediacomparaciones,maxcomparaciones,2); //DATOS DE BUSQUEDA 
	    ncomparaciones = maxcomparaciones = 0; mincomparaciones = 9999;
	    for(int i = 0 ; i < ninserciones ; ++i)
	    {
	      compactuales = tablita.in_doble(ale.get_nelem(i),0);
	      if(compactuales > maxcomparaciones)
	      {
		  maxcomparaciones = compactuales;
	      }
	      if(compactuales < mincomparaciones)
	      {
		  mincomparaciones = compactuales;
	      }
	      ncomparaciones += compactuales;
	    }
	    mediacomparaciones = (float)ncomparaciones / ninserciones;
	    tablita.estadisticas(ninserciones,ncomparaciones,mincomparaciones,mediacomparaciones,maxcomparaciones,1); //DATOS INSERCION
            break;
        case 4:
	    for(int i = 0; i < total_a_almacenar; i++)
	    {
	      tablita.in_redispersion(ale.get_nelem(i),1);
	    }
	    cout << "despues de llenar tabla" <<endl;
	    ncomparaciones = maxcomparaciones = 0;
	    mincomparaciones = 9999;
	    for(int i = 0 ; i < nbusquedas ;i++)
	    {
		cout << "for de busqeuda" <<endl;
		j = rand() % total_a_almacenar;
		compactuales = tablita.busq_redispersion(ale.get_nelem(j));
		cout << "for de busqueda despues de llamar a buscar redispersion" <<endl;
		if(compactuales > maxcomparaciones)
		{
		    maxcomparaciones = compactuales;
		}
		if(compactuales < mincomparaciones)
		{
		    mincomparaciones = compactuales;
		}
		ncomparaciones += compactuales;
	    }
	    mediacomparaciones = (float)ncomparaciones / nbusquedas;
	    tablita.estadisticas(nbusquedas,ncomparaciones,mincomparaciones,mediacomparaciones,maxcomparaciones,2); //DATOS DE BUSQUEDA 
	    ncomparaciones = maxcomparaciones = 0; mincomparaciones = 9999;
	    for(int i = 0 ; i < ninserciones ; ++i)
	    {
	      compactuales = tablita.in_redispersion(ale.get_nelem(i),0);
	      if(compactuales > maxcomparaciones)
	      {
		  maxcomparaciones = compactuales;
	      }
	      if(compactuales < mincomparaciones)
	      {
		  mincomparaciones = compactuales;
	      }
	      ncomparaciones += compactuales;
	    }
	    mediacomparaciones = (float)ncomparaciones / ninserciones;
	    tablita.estadisticas(ninserciones,ncomparaciones,mincomparaciones,mediacomparaciones,maxcomparaciones,1); //DATOS INSERCION
            break;
        default:
	    cout << "Opcion incorrecta" <<endl;
            break;
    }                                                              

    switch(met){
        case 1:
            cout << "*** Exploración Lineal ***" <<endl;
            break;
        case 2:
            cout << "*** Exploración Cuadrática ***" <<endl;
            break;
        case 3:
            cout << "*** Exploración Doble ***" <<endl;
            break;
        case 4:
            cout << "*** Exploración Redispersión ***" <<endl;
            break;
        default:
            cout << "ERROR" <<endl;
            break;
    }

    
    tablita.estadisticas(ninserciones,ncomparaciones,mincomparaciones,mediacomparaciones,maxcomparaciones,1); //DATOS DE INSERCIONES
    
    tablita.imprimir();
    
    cout << "Casillas ocupadas = " << tablita.get_ocupadas() <<endl;
    cout << "Casillas llenas = " << tablita.casillasllenas() <<endl; //comprobación efectiva de que no se insertan realmente
}