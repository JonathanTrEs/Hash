#include "clase.h"

///////////////////////////////////////////////////////////////////////////////////////// CLASE ALEATORIO ////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR
aleatorio::aleatorio(int numelem)
{
    nelem_ = numelem;
    vect_ = new int[nelem_];
    srand ( time(NULL) ); // cambiamos la semilla con la hora del sistema
    for(int i = 0 ; i < nelem_ ; ++i)
    {
        vect_[i] = rand() % 49999999 + 25000001; // valores del 25.000.001 al 75.000.000
    }
}
//DESTRUCTOR
aleatorio::~aleatorio()
{
  delete [] vect_; 
}

//GET
int aleatorio::get_nelem(int i)
{
  return vect_[i];
}

//IMPRIMIR
void aleatorio::imprimir()
{
    for(int i = 0 ; i < nelem_ ; ++i)
    {
        cout << vect_[i] <<endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////// CLASE CELDA //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR
celda::celda(int tamanio)
{
  bloques_ = new int[tamanio];
  bloq_ocupados_ = 0;
  tam_ = tamanio;
  desbordada_ = false;
  for(int i = 0 ; i < tam_ ; ++i)
  {
    bloques_[i] = 0;
  }
}

//DESTRUCTOR
celda::~celda()
{
  delete [] bloques_;
}

//GETTERS
int celda::get_tam()
{
  return tam_;
}

bool celda::get_desbordada()
{
  return desbordada_;
}

void celda::set_desbordada()
{
  desbordada_ = true;
}

//CELDA LLENA
bool celda::llena()
{
  return (tam_ == bloq_ocupados_);
}

//INSERTAR
int celda::insertar(int num, int modo) // si el modo es 1, inserción EFECTIVA
{
    if(modo == 1)
    {
        bloques_[bloq_ocupados_++] = num;
    }
    return bloq_ocupados_;
}

//IMPRIMIR
void celda::imprimir()
{
    for(int i = 0 ; i < tam_ ; ++i)
    {
        cout << bloques_[i] << " ";
    }
    cout <<endl;
}

//BUSCAR DNI EN LA CELDA
int celda::buscar(int dni)
{
    bool encontrado = false;
    int i = 0;
    int pos = -1;
    while(i < tam_ && !encontrado)
    {
        if(dni == bloques_[i])
	{
            encontrado = true;
            pos = i;
        }
        ++i;
    }
    return pos; //devuelve la pos dentro de la celda, o -1 si no la encuentra
}

//COMPRUEBA LOS BLOQUES OCUPADOS DE LA CELDA
int celda::contar_llenas()  //comprueba que el contador no falle
{
    int llenas = 0;
    for(int i = 0 ; i < tam_ ; ++i)
    {
        if(bloques_[i] != 0)
	{
            ++llenas;
        }
    }
    return llenas;
}

///////////////////////////////////////////////////////////////////////////////////// CLASE TABLA ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR
tabla::tabla(int numcel, int tambloq)
{
  nceldas_ = numcel; tam_bloque_ = tambloq;
  tabla_ = new celda*[nceldas_];
  for(int i = 0 ; i < nceldas_ ; ++i)
  {
    tabla_[i] = new celda(tam_bloque_);
  }
  ocupadas_ = 0;
}

//DESTRUCTOR
tabla::~tabla()
{
  for(int i = 0 ; i < nceldas_ ; ++i)
  {
    delete tabla_[i];
  }
  delete [] tabla_;
}

//GETTERS
int tabla::get_ocupadas()
{
  return ocupadas_;
}

//IMPRIMIR
void tabla::imprimir()
{
    for(int i = 0 ; i < nceldas_ ; ++i)
    {
        cout << "pos = " << i << " :: ";
        tabla_[i]->imprimir();
    }
}

//FUNCION HASH
int tabla::hash(int dni)
{
  srand(dni);
  return (rand() % nceldas_);
}

//FUNCION HASH AUXILIAR	
int tabla::hash_aux(int dni)
{
  return dni % nceldas_;
}

//FUNCION HASH AUXILIAR 2
int tabla::hash_aux_2(int dni, int r)
{
    int aleatorio;
    srand(dni);
    for(int i = 0 ; i < r ; ++i)
    {
         aleatorio = rand();
    }
    return aleatorio;
}

//INSERCION LINEAL
int tabla::in_lineal(int dni, int modo)
{
    int pos = hash(dni);
    int j = 0; //evitamos fallo de seg.
    bool insertado = false;
    int posinsercion, comparaciones = 0;
    while(!insertado && j < nceldas_)
    {
        if(!tabla_[pos]->llena())
	{
            posinsercion = tabla_[pos]->insertar(dni,modo);
            if(modo == 1)
	    {
                ++ocupadas_;
            }
            insertado = true;
            ++comparaciones;
        }
        else if(pos < nceldas_ - 1)
	{ //mientras no nos salgamos de la tabla, avanzamos
            tabla_[pos++]->set_desbordada();
            ++comparaciones;
        }
        else
	{
            tabla_[pos]->set_desbordada();
            pos = 0; //si nos salimos, volvemos al principio
            ++comparaciones;
        }
        ++j;
    }
    return comparaciones;
}

//BUSQUEDA LINEAL
int tabla::busq_lineal(int dni) //si pos_dentro acaba valiendo -1, no se encontró
{
    bool encontrado = false;
    int pos = hash(dni), comparaciones = 0, pos_dentro, pos_fuera, j = 0;
    int maxiteraciones = nceldas_;
    while(!encontrado && j < maxiteraciones)
    {
        pos_dentro = tabla_[pos]->buscar(dni); //buscar devuelve la pos dentro de la celda
        if(pos_dentro != -1)
	{ //si lo encuentro...
            encontrado = true;
            pos_fuera = pos;
            comparaciones += pos_dentro + 1;
        }
        else if (!tabla_[pos]->get_desbordada())
	{ //si no la encontramos y no está desbordada, no está en la tabla
            comparaciones += pos_dentro + 1;
            break;
        }
        else if(pos < nceldas_ - 1)
	{ //mientras no nos salgamos de la tabla, avanzamos
            ++pos;
            comparaciones += tabla_[0]->get_tam(); //comprobamos una celda completa, sumamos al total el tamaño del bloque
        }
        else 
	{
            pos = 0; //si nos salimos, volvemos al principio
            comparaciones += tabla_[0]->get_tam();
        }
        j++;
    }
    return comparaciones;
}

//INSERCION CUADRATICA
int tabla::in_cuadratica(int dni, int modo)
{
    int pos, j = 0, comparaciones = 0, posinsercion;
    bool insertado = false;
    int maxiteraciones = (nceldas_ - 1) / 2;
    while(!insertado && j < maxiteraciones)
    {
        pos = (hash(dni) + j*j) % nceldas_;
        if(!tabla_[pos]->llena())
	{
            posinsercion = tabla_[pos]->insertar(dni,modo);
            if(modo == 1)
	    {
                ++ocupadas_;
            }
            insertado = true;
            ++comparaciones;
        }
        else
	{
            tabla_[pos]->set_desbordada();
            ++comparaciones; //comprobamos una celda completa, sumamos al total el tamaño del bloque
        }
        ++j;
    }
    return comparaciones;
}

//BUSQUEDA CUADRATICA
int tabla::busq_cuadratica(int dni)
{
    int pos, j = 0, comparaciones = 0, posinsercion;
    bool encontrado = false;
    int maxiteraciones = (nceldas_ - 1) / 2;
    while(!encontrado && j < maxiteraciones)
    {
        pos = (hash(dni) + j*j) % nceldas_;
        posinsercion = tabla_[pos]->buscar(dni);
        if(posinsercion != -1)
	{
            encontrado = true;
            comparaciones += posinsercion + 1;
        }
        else if(!tabla_[pos]->get_desbordada())
	{
            comparaciones += posinsercion + 1;
            break;
        }
        else
	{
            comparaciones += tabla_[0]->get_tam();
        }
        ++j;
    }
    return comparaciones;
}

//INSERCION DISPERSION DOBLE
int tabla::in_doble(int dni, int modo)
{
    int pos, j = 0, comparaciones = 0, posinsercion;
    bool insertado = false;
    while(!insertado && j < nceldas_)
    {
        pos = (hash(dni) + j*(hash_aux(dni))) % nceldas_;
        if(!tabla_[pos]->llena())
	{
            posinsercion = tabla_[pos]->insertar(dni,modo);
            if(modo == 1)
	    {
                ++ocupadas_;
            }
            insertado = true;
            ++comparaciones;
        }
        else
	{
            tabla_[pos]->set_desbordada();
            ++comparaciones;
        }
        ++j;
    }
    return comparaciones;
}

//BUSQUEDA DISPERSION DOBLE
int tabla::busq_doble(int dni)
{
    int pos, j = 0, comparaciones = 0, posinsercion;
    bool encontrado = false;
    while(!encontrado && j < nceldas_)
    {
        pos = (hash(dni) + j*(hash_aux(dni))) % nceldas_;
        posinsercion = tabla_[pos]->buscar(dni);
        if(posinsercion != -1)
	{
            encontrado = true;
            comparaciones += posinsercion + 1;
        }
        else if(!tabla_[pos]->get_desbordada())
	{
            comparaciones += posinsercion + 1;
            break;
        }
        else
	{
            comparaciones += tabla_[0]->get_tam();
        }
        ++j;
    }
    return comparaciones;
}

//INSERCION REDISPERSION
int tabla::in_redispersion(int dni, int modo)
{
    int pos, r = 0, comparaciones = 0, posinsercion;
    bool insertado = false;
    while(!insertado && r < nceldas_)
    {
        pos = (hash(dni) + (hash_aux_2(dni,r))) % nceldas_;
        if(!tabla_[pos]->llena())
	{
            posinsercion = tabla_[pos]->insertar(dni,modo);
            if(modo == 1)
	    {
                ++ocupadas_;
            }
            insertado = true;
            ++comparaciones;
        }
        else
	{
            tabla_[pos]->set_desbordada();
            ++comparaciones;
        }
        ++r;
    }
    return comparaciones;
}

//BUSQUEDA REDISPERSION
int tabla::busq_redispersion(int dni)
{
    cout << "antes del while" <<endl;
    int pos, r = 0, comparaciones = 0, posinsercion;
    bool encontrado = false;
    while(!encontrado && r < nceldas_)
    {
        pos = (hash(dni) + (hash_aux_2(dni,r))) % nceldas_;
        posinsercion = tabla_[pos]->buscar(dni);
        if(posinsercion != -1)
	{
            encontrado = true;
            comparaciones += posinsercion + 1;
        }
        else if(!tabla_[pos]->get_desbordada())
	{
            comparaciones += posinsercion + 1;
            break;
        }
        else
	{
            comparaciones += tabla_[0]->get_tam();
        }
        ++r;
    }
    return comparaciones;
}

//ESTADISCAS
void tabla::estadisticas(int busquedas, int comp, int min, float media, int max, int tipo)
{
    if(tipo == 1)
    {
        cout << "Nº de inserciones " << busquedas << " comparaciones = " << comp <<endl;
        cout << "*** Inserción ***" <<endl;
    }
    else
    {
        cout << "Nº de búsquedas " << busquedas << " comparaciones = " << comp <<endl;
        cout << "*** Búsqueda ***" <<endl;
    }
    cout << "Mínimo = " << min <<endl;
    cout << "Media = " << media <<endl;
    cout << "Máximo = " << max <<endl;
}

//CONTAR CASILLAS OCUPADAS
int tabla::casillasllenas()
{
    int llenas = 0;
    for(int i = 0 ; i < nceldas_ ; ++i)
    {
        llenas += tabla_[i]->contar_llenas();
    }
    return llenas;
}

