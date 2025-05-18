using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using System.Drawing;

public class Meshvalues : MonoBehaviour
{
    // Start is called before the first frame update

    //all the values that are called by MeshFunnyGen.cs
    public int sizeX, sizeZ;
    public float radius, height, waveSpeed;
    public float[] perlinNoiseval, ampvalue;
    public bool drawGizmo,wave;
    public Slider[] ValueChanger;
    public Text[] Slidertext;
    public Gradient meshGradient;

    private void Start()
    {
        inittextvals();
    }

    //sets the values of the UI based ont eh values in this script
    private void inittextvals()
    {

        ValueChanger[0].value = sizeX;
        ValueChanger[1].value = sizeZ;
        //Checks if the mesh is considered to be immitating water
        //Sets sliders accoridngly
        if (wave) { Slidertext[0].text = "Water Width:" + sizeX;          
            Slidertext[1].text = "Water Length:" + sizeZ;
            Slidertext[2].text = "Wave Speed:" + string.Format("{0:#.00}", waveSpeed);
            ValueChanger[2].value = waveSpeed;
        }
        else { Slidertext[0].text = "Land Width:" + sizeX; 
            Slidertext[1].text = "Land Length:" + sizeZ;
            Slidertext[2].text = "Land Height:" + string.Format("{0:#.00}", height);
            ValueChanger[2].value = height;
        }
    }

    //allows the editiing of the Size of the meshes for the width
    public void widthchange()
    {
        sizeX = (int)ValueChanger[0].value;
        if (wave) { Slidertext[0].text = "Water Width:" + sizeX; }
        else{ Slidertext[0].text = "Land Width:" + sizeX; }
    }

    public void noisechange()
    {
        for (int i = 0; i != perlinNoiseval.Length; i++)
        { perlinNoiseval[i] = ValueChanger[3].value; }
        Slidertext[3].text = "Land Noise:" + string.Format("{0:#.00}", perlinNoiseval);
    }

    //allows the editiing of the Size of the land-based mesh for the height
    public void heightchange()
    {
        height = ValueChanger[2].value;
        Slidertext[2].text = "Land Height:" + string.Format("{0:#.00}", height);
    }

    //allows the editiing of the Size of the meshes for the length
    public void lengthchange()
    {
        sizeZ = (int)ValueChanger[1].value;
        if (wave) { Slidertext[1].text = "Water Length:" + sizeZ; }
        else { Slidertext[1].text = "Land Length:" + sizeZ; }
    }

    //changes the wave speed.
    //NOTE: This will automatically be applied based on how it works
    public void WSpeedchange()
    {
        waveSpeed = ValueChanger[2].value;
        Slidertext[2].text = "Wave Speed:" + " " + string.Format("{0:#.00}", waveSpeed);
    }


    //resets all values.
    public void resetValues(int size)
    {
        sizeX = size;
        sizeZ = size;
        height = 0.1f;
        if (wave) { waveSpeed = 0.01f; }
        inittextvals();
    }

    //closes project
    public void QuitProduct()
    {
        Application.Quit();
    }
}
