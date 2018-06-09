{
 "cells": [
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "%%HTML\n",
    "<table style=\"width:100%\">\n",
    "    <tr>\n",
    "    <td style=\"text-align:right\"><a target=\"_blanc\" href=\"http://www.irt-saintexupery.com/\"></a><img src=\"http://www.irt-saintexupery.com/wp-content/uploads/2015/05/logo.jpg\"> </td>\n",
    "    <td style=\"text-align:left\"><a target=\"_blanc\" href=\"http://www.irt-saintexupery.com/\"></a><img src=\"http://www.enseeiht.fr/skins/enseeiht-new/resources/img/logo-enseeiht.png\"> </td>\n",
    "     </tr>\n",
    "</table>\n",
    "<center><h1>Devloppement du robot TwIRTee</h1></center>\n",
    "<table style=\"width:100%\">\n",
    "    <tr>\n",
    "    <td></td>\n",
    "    <td style=\"text-align:right\">\n",
    "    \n",
    "    <table>\n",
    "    <tr>\n",
    "    <td>Tuteur :<br>Auteur :</td>\n",
    "    <td style=\"text-align:right\">Eric JENN<br>Sami EZZEROUALI</td>\n",
    "    </tr>\n",
    "    </table>\n",
    "    </td>\n",
    "    </tr>\n",
    "</table>\n",
    "\n",
    "\n",
    "\n",
    "\n",
    "## Simulation du modèle de positionnement par trilatération"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "collapsed": true
   },
   "outputs": [],
   "source": []
  },
  {
   "cell_type": "code",
   "execution_count": 2,
   "metadata": {
    "collapsed": true
   },
   "outputs": [],
   "source": [
    "import matplotlib.pyplot as plt\n",
    "from numpy import *\n",
    "from math import pi\n"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "\n",
    "- La fonction anchorsPosition trace l'emplacement des beacons dans le cas de 4 émetteurs en positionnement carré [0,0] [0,1] [1,1] et [1,0]\n",
    "##### TODO:\tRendre la fonction adaptable en nombre d'emetteurs, en suivant les methodes de placement évoqué dans \"Roa et al. - 2007 - Optimal placement of sensors for trilateration Re\"\n"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 3,
   "metadata": {
    "collapsed": true
   },
   "outputs": [],
   "source": [
    "\n",
    "def anchorsPosition(delta):\n",
    "\t_Xaux=[0,0,delta,delta]\n",
    "\t_Yaux=[0,delta,delta,0]\n",
    "\t_position=[_Xaux,_Yaux]\n",
    "\treturn _position;"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 4,
   "metadata": {
    "collapsed": true
   },
   "outputs": [],
   "source": [
    "\n",
    "def drawCercles(_X,_Y,_R):\n",
    "\tteta=linspace(0,2*pi,720);\n",
    "\ti=0\n",
    "\tcx=[]\n",
    "\tcy=[]\n",
    "\tfor k in range(4):\n",
    "\t\tfor i in range(720):\n",
    "\t\t\tcx.append(_X[k]+_R[k]*sin(teta[i]))\n",
    "\t\t\tcy.append(_Y[k]+_R[k]*cos(teta[i]))\n",
    "\tplt.plot(cx,cy,\"--\",color=\"LightGrey\")\n",
    "\t# plt.show()"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 5,
   "metadata": {
    "collapsed": true
   },
   "outputs": [],
   "source": [
    "\n",
    "def robotMove():\n",
    "\tt=linspace(0,10,10)\n",
    "\tx=100*t\n",
    "\ty=t**3\n",
    "\tplt.plot(x,y,\"+\",color=\"green\")\n",
    "\tplt.title(\" <+> Position du robot\")\n",
    "\tplt.show()"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": 6,
   "metadata": {},
   "outputs": [
    {
     "data": {
      "image/png": "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\n",
      "text/plain": [
       "<matplotlib.figure.Figure at 0x1e5b060d400>"
      ]
     },
     "metadata": {},
     "output_type": "display_data"
    }
   ],
   "source": [
    "\n",
    "vector=anchorsPosition(1000)\n",
    "\n",
    "xAnchors=vector[0]\n",
    "yAnchors=vector[1]\n",
    "\n",
    "plt.plot(xAnchors,yAnchors,\"o\",markersize=15,color=\"red\")\n",
    "#plt.show()\n",
    "\n",
    "Ray=[1000*sqrt(2),1000,0,1000]\n",
    "drawCercles(xAnchors,yAnchors,Ray)\n",
    "robotMove()"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "collapsed": true
   },
   "outputs": [],
   "source": []
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "collapsed": true
   },
   "outputs": [],
   "source": []
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {
    "collapsed": true
   },
   "outputs": [],
   "source": []
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "Python 3",
   "language": "python",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.6.2"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 1
}
