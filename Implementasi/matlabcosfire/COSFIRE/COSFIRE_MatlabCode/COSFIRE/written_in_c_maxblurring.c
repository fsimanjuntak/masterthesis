#include "mex.h"
/*
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2006 The MathWorks, Inc.
 */

void maxblurring(double *x, double *y, double *z, mwSize dataSizeY, mwSize dataSizeX, mwSize kernelSizeY, mwSize kernelSizeX, int kernelLoopFromY, int kernelLoopToY, int kernelLoopFromX, int kernelLoopToX)
{      
  int width,i,j,m,n,mm,nn;
  int outputSizeX, outputSizeY;
  float sum,mx,tmp;
  double kCenterX, kCenterY;
  int rowIndex, colIndex;

  outputSizeX = kernelLoopToX - kernelLoopFromX;
          
    kCenterX = kernelSizeX / 2;
    kCenterY = kernelSizeY / 2;
    
	for(i=kernelLoopFromY; i < kernelLoopToY; i++)                
	{
		for(j=kernelLoopFromX; j < kernelLoopToX; j++)      
		{
			sum = 0; mx = 0.0; tmp = 0.0;                           
			for(m = 0; m < kernelSizeY; m++)      
			{
				for(n = 0; n < kernelSizeX; n++)
				{
					rowIndex = i + m - kCenterY;
					colIndex = j + n - kCenterX;

					if(rowIndex >= 0 && rowIndex < dataSizeY && colIndex >= 0 && colIndex < dataSizeX)
                    {
                        tmp = x[dataSizeX * rowIndex + colIndex] * y[kernelSizeX * m + n];
						if (tmp > mx) {
							mx = tmp;
						}
                    }
				}
			}
			z[dataSizeX * i + j] = mx;
		}
	}
}

/* the gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
  double *x, *y, *z;  
  mwSize xmrows,xncols,ymrows,yncols;
  mwSize kernelLoopFromY, kernelLoopToY, kernelLoopFromX, kernelLoopToX;
  
  if(nrhs!=6) 
    mexErrMsgTxt("Six inputs required.");
  if(nlhs!=1) 
    mexErrMsgTxt("One output required.");
     
  /*  create a pointer to the input matrix y */
  x = mxGetPr(prhs[0]);

  /*  create a pointer to the input matrix y */
  y = mxGetPr(prhs[1]);  

  /*  get the dimensions of the matrix input x */
  xmrows = mxGetM(prhs[0]);
  xncols = mxGetN(prhs[0]);

  /*  get the dimensions of the matrix input y1 */
  ymrows = mxGetM(prhs[1]);
  yncols = mxGetN(prhs[1]);
  
  kernelLoopFromY = mxGetScalar(prhs[2]); 
  kernelLoopToY = mxGetScalar(prhs[3]); 
  kernelLoopFromX = mxGetScalar(prhs[4]); 
  kernelLoopToX = mxGetScalar(prhs[5]); 

  /*  get the dimensions of the matrix input y2 */
  
  /*  set the output pointer to the output matrix */
  plhs[0] = mxCreateDoubleMatrix(xmrows,xncols, mxREAL);
  
  /*  create a C pointer to a copy of the output matrix */
   
  z = mxGetPr(plhs[0]);
  /*  call the C subroutine */
   
  maxblurring(x,y,z,xncols,xmrows,yncols,ymrows,kernelLoopFromY, kernelLoopToY, kernelLoopFromX, kernelLoopToX);
}
