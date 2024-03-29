/*******************************************************************************************************************************//**
 *
 * @file		Infotronic.c
 * @brief		Drivers de GPIO LPC1769
 * @date		23-03-16
 * @author		Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR_gpio.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	\fn  void SetDIR ( uint8_t puerto , uint8_t bit , uint8_t dir )
	\brief Selecciona si el GPIO sera entrada o salida
 	\author Ing. Marcelo Trujillo
 	\date 30/03/2016
 	\param [in] puerto Numero del puerto seleccionado
 	\param [in] bit Numero del bit seleccionado
 	\param [in] dir seleccion entre entrada o salida

	\return void
*/
void SetDIR ( uint8_t puerto , uint8_t bit , uint8_t dir )
{
	__RW uint32_t *p = ( __RW uint32_t * )  0x2009C000 ;

	if ( dir )
		*( p + puerto * 8 ) = *( p + puerto * 8 ) | ( 1 << bit );
	else
		*( p + puerto * 8 ) = *( p + puerto * 8 ) & ( ~ ( 1 << bit ) );

}

/**
	\fn  void SetMODE ( uint8_t puerto , uint8_t bit , uint8_t modo )
	\brief Activa/Desactiva un pin
 	\author Ing. Marcelo Trujillo
 	\date 30/03/2016
 	\param [in] puerto Numero del puerto seleccionado
 	\param [in] bit Numero del bit seleccionado
 	\param [in] modo Selecciona entre los 4 modos de funcionamiento
		<ul>
			<li> Dirección de los ports
			<ol>
			<li> MODO0: SALIDA
			<li> MODO1: SALIDA
			<li> MODO2: ENTRADA
			<li> MODO3: ENTRADA
			</ol>
		</ul>
	\return void
*/
void SetMODE ( uint8_t port , uint8_t bit , uint8_t mode )
{
	__RW uint32_t *p = ( __RW uint32_t * )  0x4002C040 ;

	*( p + port * 2 + bit / 16 ) = *( p + port * 2 + bit / 16 ) & ~( 0x3 << (2 * bit));
	*( p + port * 2 + bit / 16 ) = *( p + port * 2 + bit / 16 ) | ( mode << (2 * (bit % 16)));

}

/**
	\fn  void SetPIN ( uint8_t puerto , uint8_t bit , uint8_t estado )
	\brief Activa/Desactiva un pin
 	\author Ing. Marcelo Trujillo
 	\date 30/03/2016
 	\param [in] puerto Numero del puerto seleccionado
 	\param [in] bit Numero del bit seleccionado
 	\param [in] estado 1: ON 2:OFF

	\return void
*/
void SetPIN ( uint8_t port , uint8_t bit , uint8_t state )
{
	__RW uint32_t *set = ( __RW uint32_t * )  0x2009C018 ;
	__RW uint32_t *clear = ( __RW uint32_t * )  0x2009C01C ;

	if (state)
		*( set + port * 8 ) = *( set + port * 8 ) | ( 1 << bit );
	else
		*( clear + port * 8 ) = *( clear + port * 8 ) | ( 1 << bit );

}

uint8_t GetPIN( uint8_t port , uint8_t bit , uint8_t activity )
{
	__RW uint32_t *p = ( __RW uint32_t * )  0x2009C014 ;
	uint8_t r;

	r = ( *( p + port * 8 ) >> bit ) & 1;
	if (r == activity )
		return 1;
	return 0;
}

