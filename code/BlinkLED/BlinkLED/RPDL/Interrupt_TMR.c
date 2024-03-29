/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62Nxx
* File Name		: Interrupt_TMR.c
* Version		: 1.02
* Contents		: Interrupt handlers for the Timer units
* Customer		: 
* Model			: 
* Order			: 
* CPU			: RX
* Compiler		: RXC
* OS			: Nothing
* Programmer	: 
* Note			: 
************************************************************************
* Copyright, 2011. Renesas Electronics Corporation
* and Renesas Solutions Corporation
************************************************************************
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FILE COMMENT END""**************************************************/

#include "r_pdl_tmr.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/*""FUNC COMMENT""***************************************************
* Module outline : Timer interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_TMRn_XXX(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for Timer TMR channel n
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: 
* Output		: 
*-------------------------------------------------------------------
* Use function	: R_TmrOverflowFunc[n](), R_TmrCMAFunc[n]() or
*				: R_TmrCMBFunc[n]() as appropriate.
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_TMR0_CMIA0
#pragma interrupt Interrupt_TMR0_CMA(vect=VECT_TMR0_CMIA0, fint)
#else
#pragma interrupt Interrupt_TMR0_CMA(vect=VECT_TMR0_CMIA0)
#endif
void Interrupt_TMR0_CMA(void)
{
	/* Call the user function? */
	if (rpdl_TMR_CMA_callback_func[0] != PDL_NO_FUNC)
	{
		/* Call the user function */
		rpdl_TMR_CMA_callback_func[0]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR0_CMIB0
#pragma interrupt Interrupt_TMR0_CMB(vect=VECT_TMR0_CMIB0, fint)
#else
#pragma interrupt Interrupt_TMR0_CMB(vect=VECT_TMR0_CMIB0)
#endif
void Interrupt_TMR0_CMB(void)
{
	if (rpdl_TMR_one_shot[0] != false)
	{
		/* Channel mode? */
		if (rpdl_TMR_one_shot[0] == CHANNEL_MODE)
		{
			/* Stop the channel 0 clock input */
			TMR0.TCCR.BYTE = 0x00u;
		}
		/* Unit mode? */
		else
		{
			/* Stop the channel 1 clock input */
			TMR1.TCCR.BYTE = 0x00u;
		}

		rpdl_TMR_one_shot[0] = false;

		/* Clear the interrupt request flag (the timer may have set it again) */
		ICU.IR[VECT_TMR0_CMIB0].BIT.IR = 0;
	}

	/* Call the user function? */
	if (rpdl_TMR_CMB_callback_func[0] != PDL_NO_FUNC)
	{
		rpdl_TMR_CMB_callback_func[0]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR0_OVI0
#pragma interrupt Interrupt_TMR0_OV(vect=VECT_TMR0_OVI0, fint)
#else
#pragma interrupt Interrupt_TMR0_OV(vect=VECT_TMR0_OVI0)
#endif
void Interrupt_TMR0_OV(void)
{
	/* Call the user function */
	if (rpdl_TMR_Overflow_callback_func[0] != PDL_NO_FUNC)
	{
		rpdl_TMR_Overflow_callback_func[0]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR1_CMIA1
#pragma interrupt Interrupt_TMR1_CMA(vect=VECT_TMR1_CMIA1, fint)
#else
#pragma interrupt Interrupt_TMR1_CMA(vect=VECT_TMR1_CMIA1)
#endif
void Interrupt_TMR1_CMA(void)
{
	/* Call the user function? */
	if (rpdl_TMR_CMA_callback_func[1] != PDL_NO_FUNC)
	{
		/* Call the user function */
		rpdl_TMR_CMA_callback_func[1]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR1_CMIB1
#pragma interrupt Interrupt_TMR1_CMB(vect=VECT_TMR1_CMIB1, fint)
#else
#pragma interrupt Interrupt_TMR1_CMB(vect=VECT_TMR1_CMIB1)
#endif
void Interrupt_TMR1_CMB(void)
{
	if (rpdl_TMR_one_shot[1] != false)
	{
		/* Stop the channel 1 clock input */
		TMR1.TCCR.BYTE = 0x00u;

		rpdl_TMR_one_shot[1] = false;

		/* Clear the interrupt request flag (the timer may have set it again) */
		ICU.IR[VECT_TMR1_CMIB1].BIT.IR = 0u;
	}

	/* Call the user function? */
	if (rpdl_TMR_CMB_callback_func[1] != PDL_NO_FUNC)
	{
		rpdl_TMR_CMB_callback_func[1]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR1_OVI1
#pragma interrupt Interrupt_TMR1_OV(vect=VECT_TMR1_OVI1, fint)
#else
#pragma interrupt Interrupt_TMR1_OV(vect=VECT_TMR1_OVI1)
#endif
void Interrupt_TMR1_OV(void)
{
	/* Call the user function */
	if (rpdl_TMR_Overflow_callback_func[1] != PDL_NO_FUNC)
	{
		rpdl_TMR_Overflow_callback_func[1]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR2_CMIA2
#pragma interrupt Interrupt_TMR2_CMA(vect=VECT_TMR2_CMIA2, fint)
#else
#pragma interrupt Interrupt_TMR2_CMA(vect=VECT_TMR2_CMIA2)
#endif
void Interrupt_TMR2_CMA(void)
{
	/* Call the user function? */
	if (rpdl_TMR_CMA_callback_func[2] != PDL_NO_FUNC)
	{
		/* Call the user function */
		rpdl_TMR_CMA_callback_func[2]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR2_CMIB2
#pragma interrupt Interrupt_TMR2_CMB(vect=VECT_TMR2_CMIB2, fint)
#else
#pragma interrupt Interrupt_TMR2_CMB(vect=VECT_TMR2_CMIB2)
#endif
void Interrupt_TMR2_CMB(void)
{
	if (rpdl_TMR_one_shot[2] != false)
	{
		/* Channel mode? */
		if (rpdl_TMR_one_shot[2] == CHANNEL_MODE)
		{
			/* Stop the channel 2 clock input */
			TMR2.TCCR.BYTE = 0x00u;
		}
		/* Unit mode? */
		else
		{
			/* Stop the channel 3 clock input */
			TMR3.TCCR.BYTE = 0x00u;
		}

		rpdl_TMR_one_shot[2] = false;

		/* Clear the interrupt request flag (the timer may have set it again) */
		ICU.IR[VECT_TMR2_CMIB2].BIT.IR = 0;
	}

	/* Call the user function? */
	if (rpdl_TMR_CMB_callback_func[2] != PDL_NO_FUNC)
	{
		rpdl_TMR_CMB_callback_func[2]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR2_OVI2
#pragma interrupt Interrupt_TMR2_OV(vect=VECT_TMR2_OVI2, fint)
#else
#pragma interrupt Interrupt_TMR2_OV(vect=VECT_TMR2_OVI2)
#endif
void Interrupt_TMR2_OV(void)
{
	/* Call the user function */
	if (rpdl_TMR_Overflow_callback_func[2] != PDL_NO_FUNC)
	{
		rpdl_TMR_Overflow_callback_func[2]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR3_CMIA3
#pragma interrupt Interrupt_TMR3_CMA(vect=VECT_TMR3_CMIA3, fint)
#else
#pragma interrupt Interrupt_TMR3_CMA(vect=VECT_TMR3_CMIA3)
#endif
void Interrupt_TMR3_CMA(void)
{
	/* Call the user function? */
	if (rpdl_TMR_CMA_callback_func[3] != PDL_NO_FUNC)
	{
		/* Call the user function */
		rpdl_TMR_CMA_callback_func[3]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR3_CMIB3
#pragma interrupt Interrupt_TMR3_CMB(vect=VECT_TMR3_CMIB3, fint)
#else
#pragma interrupt Interrupt_TMR3_CMB(vect=VECT_TMR3_CMIB3)
#endif
void Interrupt_TMR3_CMB(void)
{
	if (rpdl_TMR_one_shot[3] != false)
	{
		/* Stop the channel 3 clock input */
		TMR3.TCCR.BYTE = 0x00u;

		rpdl_TMR_one_shot[3] = false;

		/* Clear the interrupt request flag (the timer may have set it again) */
		ICU.IR[VECT_TMR3_CMIB3].BIT.IR = 0;
	}

	/* Call the user function? */
	if (rpdl_TMR_CMB_callback_func[3] != PDL_NO_FUNC)
	{
		rpdl_TMR_CMB_callback_func[3]();
	}
}

#if FAST_INTC_VECTOR == VECT_TMR3_OVI3
#pragma interrupt Interrupt_TMR3_OV(vect=VECT_TMR3_OVI3, fint)
#else
#pragma interrupt Interrupt_TMR3_OV(vect=VECT_TMR3_OVI3)
#endif
void Interrupt_TMR3_OV(void)
{
	/* Call the user function */
	if (rpdl_TMR_Overflow_callback_func[3] != PDL_NO_FUNC)
	{
		rpdl_TMR_Overflow_callback_func[3]();
	}
}
/* End of file */
