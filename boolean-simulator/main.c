/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"
#include <string.h>

static Circuit *a_Circuit()
{
	char *ATitle = "partA";

	int AINPUTS = 2;
	Boolean *x1 = new_Boolean(false);
	Boolean *y1 = new_Boolean(false);
	Boolean **AInput = new_Boolean_array(AINPUTS);
	AInput[0] = x1;
	AInput[1] = y1;

	int AOUTPUTS = 1;
	Boolean *AResult = new_Boolean(false);
	Boolean **AOutput = new_Boolean_array(AOUTPUTS);
	AOutput[0] = AResult;

	int ANGATES = 3;
	Gate *AA = new_AndGate();
	Gate *AN = new_Inverter();
	Gate *AO = new_OrGate();
	Gate **AGates = new_Gate_array(ANGATES);
	AGates[0] = AA;
	AGates[1] = AN;
	AGates[2] = AO;

	Circuit *ACircuit = new_Circuit(ATitle,
									AINPUTS, AInput,
									AOUTPUTS, AOutput,
									ANGATES, AGates);

	// AND gate
	Circuit_connect(ACircuit, x1, Gate_getInput(AA, 0));
	Circuit_connect(ACircuit, y1, Gate_getInput(AA, 1));
	Boolean *x_and_y = Gate_getOutput(AA);

	// NOT gate
	Circuit_connect(ACircuit, x1, Gate_getInput(AN, 0));
	Boolean *not_x = Gate_getOutput(AN);

	// OR gate
	Circuit_connect(ACircuit, x_and_y, Gate_getInput(AO, 0));
	Circuit_connect(ACircuit, not_x, Gate_getInput(AO, 1));
	Boolean *x_and_y_or_not_x = Gate_getOutput(AO);

	Circuit_connect(ACircuit, x_and_y_or_not_x, AResult);

	return ACircuit;
}

static Circuit *b_Circuit()
{
	char *BTitle = "partB";

	int BINPUTS = 2;
	Boolean *x1 = new_Boolean(false);
	Boolean *y1 = new_Boolean(false);
	Boolean **BInput = new_Boolean_array(BINPUTS);
	BInput[0] = x1;
	BInput[1] = y1;

	int BOUTPUTS = 1;
	Boolean *BResult = new_Boolean(false);
	Boolean **BOutput = new_Boolean_array(BOUTPUTS);
	BOutput[0] = BResult;

	int BNGATES = 3;
	Gate *BO1 = new_NorGate();
	Gate *BO2 = new_NorGate();
	Gate *BO3 = new_NorGate();
	Gate **BGates = new_Gate_array(BNGATES);
	BGates[0] = BO1;
	BGates[1] = BO2;
	BGates[2] = BO3;

	Circuit *BCircuit = new_Circuit(BTitle,
									BINPUTS, BInput,
									BOUTPUTS, BOutput,
									BNGATES, BGates);

	Circuit_connect(BCircuit, x1, Gate_getInput(BO1, 0));
	Circuit_connect(BCircuit, y1, Gate_getInput(BO1, 1));
	Boolean *x_or_y_1 = Gate_getOutput(BO1);

	Circuit_connect(BCircuit, y1, Gate_getInput(BO2, 0));
	Circuit_connect(BCircuit, x1, Gate_getInput(BO2, 1));
	Boolean *x_or_y_2 = Gate_getOutput(BO2);

	Circuit_connect(BCircuit, x_or_y_1, Gate_getInput(BO3, 0));
	Circuit_connect(BCircuit, x_or_y_2, Gate_getInput(BO3, 1));
	Boolean *x_or_y_1_or_x_or_y_2 = Gate_getOutput(BO3);

	Circuit_connect(BCircuit, x_or_y_1_or_x_or_y_2, BResult);

	return BCircuit;
}

static Circuit *c_Circuit()
{
	char *CTitle = "partC";

	int CINPUTS = 3;
	Boolean *x1 = new_Boolean(false);
	Boolean *y1 = new_Boolean(false);
	Boolean *z1 = new_Boolean(false);
	Boolean **CInput = new_Boolean_array(CINPUTS);
	CInput[0] = x1;
	CInput[1] = y1;
	CInput[2] = z1;

	int COUTPUTS = 1;
	Boolean *CResult = new_Boolean(false);
	Boolean **COutputs = new_Boolean_array(COUTPUTS);
	COutputs[0] = CResult;

	int CNGATES = 8;
	Gate *CN1 = new_Inverter();
	Gate *CN2 = new_Inverter();
	Gate *CN3 = new_Inverter();
	Gate *CO1 = new_OrGate();
	Gate *CO2 = new_OrGate();
	Gate *CO3 = new_OrGate();
	Gate *CA1 = new_AndGate();
	Gate *CA2 = new_AndGate();
	Gate **gates = new_Gate_array(CNGATES);
	gates[0] = CN1;
	gates[1] = CN2;
	gates[2] = CN3;
	gates[3] = CO1;
	gates[4] = CO2;
	gates[5] = CO3;
	gates[6] = CA1;
	gates[7] = CA2;

	Circuit *circuit = new_Circuit(CTitle,
								   CINPUTS, CInput,
								   COUTPUTS, COutputs,
								   CNGATES, gates);

	// NOTs
	Circuit_connect(circuit, x1, Gate_getInput(CN1, 0));
	Circuit_connect(circuit, y1, Gate_getInput(CN2, 0));
	Circuit_connect(circuit, z1, Gate_getInput(CN3, 0));
	Boolean *not_x = Gate_getOutput(CN1);
	Boolean *not_y = Gate_getOutput(CN2);
	Boolean *not_z = Gate_getOutput(CN3);

	// first OR
	Circuit_connect(circuit, x1, Gate_getInput(CO1, 0));
	Circuit_connect(circuit, not_y, Gate_getInput(CO1, 1));
	Boolean *x_or_not_y = Gate_getOutput(CO1);

	// second OR
	Circuit_connect(circuit, y1, Gate_getInput(CO2, 0));
	Circuit_connect(circuit, not_z, Gate_getInput(CO2, 1));
	Boolean *y_or_not_z = Gate_getOutput(CO2);

	// third OR
	Circuit_connect(circuit, z1, Gate_getInput(CO3, 0));
	Circuit_connect(circuit, not_x, Gate_getInput(CO3, 1));
	Boolean *z_or_not_x = Gate_getOutput(CO3);

	// first AND
	Circuit_connect(circuit, x_or_not_y, Gate_getInput(CA1, 0));
	Circuit_connect(circuit, y_or_not_z, Gate_getInput(CA1, 1));
	Boolean *x_or_not_y_and_y_or_not_z = Gate_getOutput(CA1);

	// second AND
	Circuit_connect(circuit, x_or_not_y_and_y_or_not_z, Gate_getInput(CA2, 0));
	Circuit_connect(circuit, z_or_not_x, Gate_getInput(CA2, 1));
	Boolean *x_or_not_y_and_y_or_not_z_and_z_or_not_x = Gate_getOutput(CA2);

	Circuit_connect(circuit, x_or_not_y_and_y_or_not_z_and_z_or_not_x, CResult);

	return circuit;
}

static Circuit *ec_Circuit()
{
	char *EcTitle = "ExtraCredit";

	int ECINPUTS = 3;
	Boolean *a1 = new_Boolean(false);
	Boolean *b1 = new_Boolean(false);
	Boolean *c1 = new_Boolean(false);
	Boolean **ECInput = new_Boolean_array(ECINPUTS);
	ECInput[0] = a1;
	ECInput[1] = b1;
	ECInput[2] = c1;

	// int ECOUTPUTS = 1;
	int ECOUTPUTS = 2;

	Boolean *f1 = new_Boolean(false);
	Boolean *g1 = new_Boolean(false);
	Boolean **ECOutputs = new_Boolean_array(ECOUTPUTS);
	ECOutputs[0] = f1;
	ECOutputs[1] = g1;

	int ECNGATES = 24;
	Gate *ECN1 = new_Inverter();
	Gate *ECN2 = new_Inverter();
	Gate *ECN3 = new_Inverter();
	Gate *ECO1 = new_OrGate();
	Gate *ECO2 = new_OrGate();
	Gate *ECO3 = new_OrGate();
	Gate *ECA1 = new_AndGate();
	Gate *ECA2 = new_AndGate();
	Gate *ECA3 = new_AndGate();
	Gate *ECA4 = new_AndGate();
	Gate *ECA5 = new_AndGate();
	Gate *ECA6 = new_AndGate();
	Gate *ECA7 = new_AndGate();
	Gate *ECA8 = new_AndGate();
	Gate *GECA1 = new_AndGate();
	Gate *GECA2 = new_AndGate();
	Gate *GECA3 = new_AndGate();
	Gate *GECA4 = new_AndGate();
	Gate *GECA5 = new_AndGate();
	Gate *GECA6 = new_AndGate();
	Gate *GECA7 = new_AndGate();
	Gate *GECO1 = new_OrGate();
	Gate *GECO2 = new_OrGate();
	Gate *GECO3 = new_OrGate();

	Gate **gates = new_Gate_array(ECNGATES);
	gates[0] = ECN1;
	gates[1] = ECN2;
	gates[2] = ECN3;
	gates[3] = ECA1;
	gates[4] = ECA2;
	gates[5] = ECA3;
	gates[6] = ECA4;
	gates[7] = ECA5;
	gates[8] = ECA6;
	gates[9] = ECA7;
	gates[10] = ECA8;
	gates[11] = ECO1;
	gates[12] = ECO2;
	gates[13] = ECO3;
	gates[14] = GECA1;
	gates[15] = GECA2;
	gates[16] = GECA3;
	gates[17] = GECA4;
	gates[18] = GECA5;
	gates[19] = GECA6;
	gates[20] = GECA7;
	gates[21] = GECO1;
	gates[22] = GECO2;
	gates[23] = GECO3;

	Circuit *Eccircuit = new_Circuit(EcTitle,
									 ECINPUTS, ECInput,
									 ECOUTPUTS, ECOutputs,
									 ECNGATES, gates);

	// NOTs
	Circuit_connect(Eccircuit, a1, Gate_getInput(ECN1, 0));
	Circuit_connect(Eccircuit, b1, Gate_getInput(ECN2, 0));
	Circuit_connect(Eccircuit, c1, Gate_getInput(ECN3, 0));
	Boolean *not_a = Gate_getOutput(ECN1);
	Boolean *not_b = Gate_getOutput(ECN2);
	Boolean *not_c = Gate_getOutput(ECN3);

	// !a AND !b
	Circuit_connect(Eccircuit, not_a, Gate_getInput(ECA1, 0));
	Circuit_connect(Eccircuit, not_b, Gate_getInput(ECA1, 1));
	Boolean *not_a_AND_not_b = Gate_getOutput(ECA1);

	// !aANDb
	Circuit_connect(Eccircuit, not_a, Gate_getInput(ECA2, 0));
	Circuit_connect(Eccircuit, b1, Gate_getInput(ECA2, 1));
	Boolean *not_a_AND_b = Gate_getOutput(ECA2);

	// aAND!b
	Circuit_connect(Eccircuit, a1, Gate_getInput(ECA3, 0));
	Circuit_connect(Eccircuit, not_b, Gate_getInput(ECA3, 1));
	Boolean *a_AND_not_b = Gate_getOutput(ECA3);

	// aANDb
	Circuit_connect(Eccircuit, a1, Gate_getInput(ECA4, 0));
	Circuit_connect(Eccircuit, b1, Gate_getInput(ECA4, 1));
	Boolean *a_AND_b = Gate_getOutput(ECA4);

	//! aAND!b AND c
	Circuit_connect(Eccircuit, not_a_AND_not_b, Gate_getInput(ECA5, 0));
	Circuit_connect(Eccircuit, c1, Gate_getInput(ECA5, 1));
	Boolean *not_a_AND_not_b_AND_c = Gate_getOutput(ECA5);

	//! aANDb AND !c
	Circuit_connect(Eccircuit, not_a_AND_b, Gate_getInput(ECA6, 0));
	Circuit_connect(Eccircuit, not_c, Gate_getInput(ECA6, 1));
	Boolean *not_a_AND_b_AND_not_c = Gate_getOutput(ECA6);

	// aAND!b AND !c
	Circuit_connect(Eccircuit, a_AND_not_b, Gate_getInput(ECA7, 0));
	Circuit_connect(Eccircuit, not_c, Gate_getInput(ECA7, 1));
	Boolean *a_AND_not_b_AND_not_c = Gate_getOutput(ECA7);

	// aANDb AND !c
	Circuit_connect(Eccircuit, a_AND_b, Gate_getInput(ECA8, 0));
	Circuit_connect(Eccircuit, not_c, Gate_getInput(ECA8, 1));
	Boolean *a_AND_b_AND_not_c = Gate_getOutput(ECA8);

	//! a!bc + !ab!c
	Circuit_connect(Eccircuit, not_a_AND_not_b_AND_c, Gate_getInput(ECO1, 0));
	Circuit_connect(Eccircuit, not_a_AND_b_AND_not_c, Gate_getInput(ECO1, 1));
	Boolean *not_a_AND_not_b_AND_c_OR_not_a_AND_b_AND_no_c = Gate_getOutput(ECO1);

	// a!b!c + ab!c
	Circuit_connect(Eccircuit, a_AND_not_b_AND_not_c, Gate_getInput(ECO2, 0));
	Circuit_connect(Eccircuit, a_AND_b_AND_not_c, Gate_getInput(ECO2, 1));
	Boolean *a_AND_not_b_AND_not_c_OR_a_AND_b_AND_not_c = Gate_getOutput(ECO2);

	// f output
	Circuit_connect(Eccircuit, not_a_AND_not_b_AND_c_OR_not_a_AND_b_AND_no_c, Gate_getInput(ECO3, 0));
	Circuit_connect(Eccircuit, a_AND_not_b_AND_not_c_OR_a_AND_b_AND_not_c, Gate_getInput(ECO3, 1));
	Boolean *fOutput = Gate_getOutput(ECO3);

	Circuit_connect(Eccircuit, fOutput, f1);

	//! aANDb AND c
	Circuit_connect(Eccircuit, not_a_AND_b, Gate_getInput(GECA2, 0));
	Circuit_connect(Eccircuit, c1, Gate_getInput(GECA2, 1));
	Boolean *not_a_AND_b_AND_c = Gate_getOutput(GECA2);

	// aAND!b AND c
	Circuit_connect(Eccircuit, a_AND_not_b, Gate_getInput(GECA4, 0));
	Circuit_connect(Eccircuit, c1, Gate_getInput(GECA4, 1));
	Boolean *a_AND_not_b_AND_c = Gate_getOutput(GECA4);

	// aANDb AND c
	Circuit_connect(Eccircuit, a_AND_b, Gate_getInput(GECA6, 0));
	Circuit_connect(Eccircuit, c1, Gate_getInput(GECA6, 1));
	Boolean *a_AND_b_AND_c = Gate_getOutput(GECA6);

	//! a!bc + !abc
	Circuit_connect(Eccircuit, not_a_AND_not_b_AND_c, Gate_getInput(GECO1, 0));
	Circuit_connect(Eccircuit, not_a_AND_b_AND_c, Gate_getInput(GECO1, 1));
	Boolean *not_A_AND_not_b_AND_c_OR_not_a_AND_b_AND_c = Gate_getOutput(GECO1);

	// a!bc + abc
	Circuit_connect(Eccircuit, a_AND_not_b_AND_c, Gate_getInput(GECO2, 0));
	Circuit_connect(Eccircuit, a_AND_b_AND_c, Gate_getInput(GECO2, 1));
	Boolean *a_AND_not_b_AND_c_OR_a_AND_b_AND_c = Gate_getOutput(GECO2);

	// g output
	Circuit_connect(Eccircuit, not_A_AND_not_b_AND_c_OR_not_a_AND_b_AND_c, Gate_getInput(GECO3, 0));
	Circuit_connect(Eccircuit, a_AND_not_b_AND_c_OR_a_AND_b_AND_c, Gate_getInput(GECO3, 1));
	Boolean *gOutput = Gate_getOutput(GECO3);

	Circuit_connect(Eccircuit, gOutput, g1);

	return Eccircuit;
}

static void test3In1Out(Circuit *circuit, bool in0, bool in1, bool in2)
{
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	Circuit_update(circuit);
	printf("%s %s %s -> %s\n",
		   Boolean_toString(Circuit_getInput(circuit, 0)),
		   Boolean_toString(Circuit_getInput(circuit, 1)),
		   Boolean_toString(Circuit_getInput(circuit, 2)),
		   Boolean_toString(Circuit_getOutput(circuit, 0)));
}

static void test3In2Out(Circuit *circuit, bool in0, bool in1, bool in2)
{
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	Circuit_update(circuit);
	printf("%s %s %s -> %s, %s\n",
		   Boolean_toString(Circuit_getInput(circuit, 0)),
		   Boolean_toString(Circuit_getInput(circuit, 1)),
		   Boolean_toString(Circuit_getInput(circuit, 2)),
		   Boolean_toString(Circuit_getOutput(circuit, 0)),
		   Boolean_toString(Circuit_getOutput(circuit, 1)));
}

static void Test2In1Out(Circuit *circuit, bool in0, bool in1)
{
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_update(circuit);

	printf("%s %s -> %s\n",
		   Boolean_toString(Circuit_getInput(circuit, 0)),
		   Boolean_toString(Circuit_getInput(circuit, 1)),
		   Boolean_toString(Circuit_getOutput(circuit, 0)));
}

void userInput()
{
    Circuit *ACircuit = a_Circuit();
    Circuit_dump(ACircuit);
    printf("\n");

    printf("Testing: false false: should be true\n");
    Test2In1Out(ACircuit, false, false);

    printf("Testing: false true: should be true\n");
    Test2In1Out(ACircuit, false, true);

    printf("TEsting: true false: should be false\n");
    Test2In1Out(ACircuit, true, false);

    printf("Testing: true true: should be true\n");
    Test2In1Out(ACircuit, true, true);

    Circuit_free(ACircuit);

    Circuit *BCircuit = b_Circuit();
    Circuit_dump(BCircuit);
    printf("\n");

    printf("Testing: false false: should be false\n");
    Test2In1Out(BCircuit, false, false);

    printf("Testing: false true: should be true\n");
    Test2In1Out(BCircuit, false, true);

    printf("Testing: true false: should be true\n");
    Test2In1Out(BCircuit, true, false);

    printf("Testing: true true: should be true\n");
    Test2In1Out(BCircuit, true, true);

    Circuit_free(BCircuit);

    Circuit *CCircuit = c_Circuit();
    Circuit_dump(CCircuit);
    printf("\n");

    printf("Testing: false false false: should be true\n");
    test3In1Out(CCircuit, false, false, false);

    printf("Testing: false false true: should be false\n");
    test3In1Out(CCircuit, false, false, true);

    printf("Testing: false true false: should be false\n");
    test3In1Out(CCircuit, false, true, false);

    printf("Testing: false true true: should be false\n");
    test3In1Out(CCircuit, false, true, true);

    printf("Testing: true false false: should be false\n");
    test3In1Out(CCircuit, true, false, false);

    printf("Testing: true false true: should be false\n");
    test3In1Out(CCircuit, true, false, true);

    printf("Testing: true true false: should be false\n");
    test3In1Out(CCircuit, true, true, false);

    printf("Testing: true true true: should be true\n");
    test3In1Out(CCircuit, true, true, true);

    Circuit_free(CCircuit);

    Circuit *ECCircuit = ec_Circuit();
    Circuit_dump(ECCircuit);
    printf("\n");

    printf("Testing: false false false: f should be false, g should be false\n");
    test3In2Out(ECCircuit, false, false, false);

    printf("Testing: false false true: f should be true, g should be true\n");
    test3In2Out(ECCircuit, false, false, true);

    printf("Testing: false true false: f should be true, g should be false\n");
    test3In2Out(ECCircuit, false, true, false);

    printf("Testing: false true true: f should be false, g should be true\n");
    test3In2Out(ECCircuit, false, true, true);

    printf("Testing: true false false: f should be true, g should be false\n");
    test3In2Out(ECCircuit, true, false, false);

    printf("Testing: true false true: f should be false, g should be true\n");
    test3In2Out(ECCircuit, true, false, true);

    printf("Testing: true true false: f should be true, g should be false\n");
    test3In2Out(ECCircuit, true, true, false);

    printf("Testing: true true true: f should be false, g should be true\n");
    test3In2Out(ECCircuit, true, true, true);

    Circuit_free(ECCircuit);
}

int main(int argc, char **argv)
{
	userInput();
}