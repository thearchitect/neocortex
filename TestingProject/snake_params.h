#include "control_value.h"
#include "resource1.h"

#pragma once

struct SnakeParams{

	ControlValue<float> alpha;
	ControlValue<float> beta;
	ControlValue<float> gamma;
	ControlValue<float> kappa;
	int window;

	SnakeParams()
	{
		alpha.set(0.0);
		beta.set(0.0);
		gamma.set(0.0);
		kappa.set(0.0);

		window = 2;
	}

	SnakeParams(HWND parent)
	{
		alpha.bind(parent, IDC_EDIT_A);
		beta.bind(parent, IDC_EDIT_B);
		gamma.bind(parent, IDC_EDIT_G);
		kappa.bind(parent, IDC_EDIT_K);

		window = 2;
	}

	void read()
	{
		alpha.read();
		beta.read();
		gamma.read();
		kappa.read();
	}
};