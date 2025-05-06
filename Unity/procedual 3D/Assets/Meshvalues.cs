using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using System.Drawing;

public class Meshvalues : MonoBehaviour
{
    // Start is called before the first frame update

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

    private void inittextvals()
    {

        ValueChanger[0].value = sizeX;
        ValueChanger[1].value = sizeZ;
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

    public void heightchange()
    {
        height = ValueChanger[2].value;
        Slidertext[2].text = "Land Height:" + string.Format("{0:#.00}", height);
    }

    public void lengthchange()
    {
        sizeZ = (int)ValueChanger[1].value;
        if (wave) { Slidertext[1].text = "Water Length:" + sizeZ; }
        else { Slidertext[1].text = "Land Length:" + sizeZ; }
    }

    public void WSpeedchange()
    {
        waveSpeed = ValueChanger[2].value;
        Slidertext[2].text = "Wave Speed:" + " " + string.Format("{0:#.00}", waveSpeed);
    }

    public void resetValues(int size)
    {
        sizeX = size;
        sizeZ = size;
        height = 0.1f;
        if (wave) { waveSpeed = 0.01f; }
        inittextvals();
    }
    public void QuitProduct()
    {
        Application.Quit();
    }
}
