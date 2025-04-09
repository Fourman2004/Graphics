using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class Meshvalues : MonoBehaviour
{
    // Start is called before the first frame update

    public int sizeX, sizeZ;
    public float radius, height, perlinNoiseval, waveSpeed;
    public bool drawGizmo,wave;
    public Slider[] ValueChanger;
    public Text[] Slidertext;


    private void Start()
    {
        if (wave) { Slidertext[0].text = "Water Width:" + sizeX;
            Slidertext[1].text = "Water Length:" + sizeZ;
            Slidertext[2].text = "Wave Speed:" + string.Format("{0:#.00}", waveSpeed);
        }
        else { Slidertext[0].text = "Land Width:" + sizeX; 
            Slidertext[1].text = "Land Length:" + sizeZ;
            Slidertext[2].text = "Land Height:" + string.Format("{0:#.00}", height);
        }
    }
    public void widthchange()
    {
        sizeX = (int)ValueChanger[0].value;
        if (wave) { Slidertext[0].text = "Water Width:" + sizeX; }
        else{ Slidertext[0].text = "Land Width:" + sizeX; }
    }

    public void heightchange()
    {
        height = ValueChanger[2].value;
        perlinNoiseval = (ValueChanger[2].value / 10.0f);
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

    public void QuitProduct()
    {
        Application.Quit();
    }
}
