using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.LowLevelPhysics;
using UnityEngine.UI;

[RequireComponent(typeof(MeshFilter))]
public class MeshFunnygen : MonoBehaviour
{
    Mesh m_TheMesh;
    Vector3[] verts;
    int[] tris;
    Vector2[] UV;
    Color[] meshColours;
    float terrainHigh, terrainLow;
    Vector3 vertex;

     public Meshvalues MV;
    // Start is called before the first frame update
    void Start()
    {
        m_TheMesh = new Mesh();
        GetComponent<MeshFilter>().mesh = m_TheMesh;
        dataForTerrain();
        if (!MV.wave) {generateMesh(); }
    }

    private void Update()
    {
        if (MV.wave) { wave(Time.timeSinceLevelLoad*MV.waveSpeed);
            generateMesh();
        }
    }

    public void dataForTerrain()
    {

        verts = new Vector3[(MV.sizeX + 1) * (MV.sizeZ + 1)];

       
        for (int index = 0, i = 0; i <= MV.sizeZ; i++)
        {
            for (int j = 0; j <= MV.sizeX; j++)
            {
                if (!MV.wave)
                {
                    float k = Mathf.PerlinNoise(i * MV.perlinNoiseval, j * MV.perlinNoiseval) * MV.height;

                    if (k > terrainHigh) { terrainHigh = k; }
                    if (k < terrainLow) { terrainLow = k; }
                    verts[index] = new Vector3(j, k, i);
                }
                else { verts[index] = new Vector3(j, vertex.y, i);}
                    index++;
            }
        }

        tris = new int[(MV.sizeX *MV.sizeZ)*6];
        int triangle = 0, vert = 0;
        for (int i = 0; i < MV.sizeZ; i++)
        {
            for (int j = 0; j < MV.sizeX; j++)
            {
                tris[triangle + 0] = vert + 0;
                tris[triangle + 1] = vert + MV.sizeX + 1;
                tris[triangle + 2] = vert + 1;
                tris[triangle + 3] = vert + 1;
                tris[triangle + 4] = vert + MV.sizeX + 1;
                tris[triangle + 5] = vert + MV.sizeX + 2;

                vert++;
                triangle+=6;
            }
            vert++;
        }

        UV = new Vector2[verts.Length];
        for (int index = 0, i = 0; i <= MV.sizeZ; i++)
        {
            for (int j = 0; j <= MV.sizeX; j++)
            {
                UV[index] = new Vector2((float)j/MV.sizeX, (float)i/MV.sizeZ);
                index++;
            }
        }

        meshColours = new Color[verts.Length];
        for (int index = 0, i = 0; i <= MV.sizeZ; i++)
        {
            for (int j = 0; j <= MV.sizeX; j++)
            {
                float meshheight = Mathf.InverseLerp(terrainHigh,terrainLow,verts[index].y);
                meshColours[index] = MV.meshGradient.Evaluate(meshheight);
                index++;
            }
        }
    }

   public void generateMesh()
    {
        m_TheMesh.Clear();

        m_TheMesh.vertices = verts;
        m_TheMesh.triangles = tris;
        m_TheMesh.uv = UV;
        m_TheMesh.colors = meshColours;
        m_TheMesh.RecalculateNormals();
    }


    void wave(float time)
    {
        for(int i = 0; i < verts.Length;i++)
        {
            vertex = verts[i];
            vertex.y = Mathf.Sin(time*vertex.x);
            if (vertex.y > terrainHigh) { terrainHigh = vertex.y; }
            if (vertex.y < terrainLow) { terrainLow = vertex.y; }
            verts[i] = vertex;
        }
    }
    private void OnDrawGizmos()
    {
        if (verts == null){return;}

        if (MV.drawGizmo)
        {
            for (int i = 0; i < verts.Length; i++)
            {
                Gizmos.DrawSphere(verts[i], MV.radius);
            }
        }
    }
}
