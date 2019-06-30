/**
 	\file KitInfo2PR_Timer.c
 	\brief Primitivas de Temporizadores
 	\details Validas para el kit completo
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"
extern volatile TIEMPOS TmrRun[TIMERS] ;					//!< Buffer de Temporizadores
extern volatile EVENTOS Evento[TIMERS] ;					//!< Buffer de eventos vencidos

/**
	\fn  void TimerStart( int Ev , TIEMPOS Sc )
	\brief Disparo de un temporizador
 	\param [in] Ev numero temporizador
 	\param [in] duracion
	\return void
*/
void TimerStart( int Ev , TIEMPOS Sc )
{
	if( Sc )
	{
		TmrRun[ Ev ] = Sc ;
  		Evento [ Ev ] = 0 ;
	}
	else
	{
		TmrRun[ Ev ]=0;
  		Evento [ Ev ] = 1;
	}
}

/**
	\fn  void TimerStop( int Ev )
	\brief Reset de un temporizador
 	\param [in] Ev numero temporizador
 	\return void
*/
void TimerStop( int Ev )
{
	TmrRun[ Ev ] = 0 ;
	Evento [ Ev ] = 0 ;
}

/**
	\fn  void TimerEvent( void )
	\brief Analisis de los temporizadores vencidos
 	\param void
 	\return void
*/
void TimerEvent( void )
{
	int j  ;
    
	for( j = 0; j < TIMERS ; j ++ )
   	{
      	if( Evento[ j ] )
      	{		
	      	switch( j ) 
      	  	{
   		        case E_00:
   		        	Led ( LED0 , OFF );
   		        	Led ( LED1 , ON );
   		        	Led ( LED2 , OFF );

	   		        TimerStart( E_01 , T_01 );
       				Evento[ E_00 ] = 0;
       				break;
   		        case E_01:
   		        	Led ( LED0 , OFF );
   		        	Led ( LED1 , OFF );
   		        	Led ( LED2 , ON );
	   		        TimerStart( E_02 , T_02 );
       				Evento[ E_01 ] = 0;
       				break;
   		        case E_02:
   		        	Led ( LED0 , ON );
   		        	Led ( LED1 , OFF );
   		        	Led ( LED2 , OFF );

	   		        TimerStart( E_00 , T_00 );
       				Evento[ E_02 ] = 0;
       				break;
     	  	}
        }   
    }
}

/**
	\fn void AnalizarTimer( int t)
	\brief decremento de un temporizador activo
 	\param [in] Ev numero temporizador
 	\return void
*/
void AnalizarTimer( int t)
{
	if(TmrRun[t])
   	{
   		TmrRun[t] --;
	   	if( !TmrRun[t] )
   	  		Evento [t] = 1;
	}
}
