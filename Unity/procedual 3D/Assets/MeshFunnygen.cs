using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.LowLevelPhysics;
using UnityEngine.UI;


///The orefab MUST have a meshfilter, otherwise it won't work
[RequireComponent(typeof(MeshFilter))]
public class MeshFunnygen : MonoBehaviour
{
    //The mesh that will be generated
    Mesh m_TheMesh;

    //An array of verticies
    Vector3[] verts;

    //an array of the triangeles
    int[] tris;

    //the UV's for the mesh
    Vector2[] uv;

    //a gradiant that will be used for the Height
    Color[] meshColours;

    //The height
    float terrainHigh, terrainLow;
    //A value that will be used for calculating waveheight
    Vector3 vertex;

    //refernce to a script that will hold all the values.
     public Meshvalues MV;

    // Start is called before the first frame update
    void Start()
    {
        //makes a new mesh object
        m_TheMesh = new Mesh();
        //sets the meshfilter to be the mesh
        GetComponent<MeshFilter>().mesh = m_TheMesh;
        //generates the data for the mesh.
        dataForTerrain();
        //if the bool for the mesh isn't set, it will generate it.
        if (!MV.wave) {generateMesh(); }
    }

    private void Update()
    {
        //gets the twime since the game was opened, and multiplies it by a set speed, which can be adjustable.
        if (MV.wave) { wave(Time.timeSinceLevelLoad*MV.waveSpeed);
            generateMesh();
        }
    }

    public void dataForTerrain()
    {
        Verticies()
        Triangles()
        UV()
        colour();
    }

    void UV()
    {
        //Gets new UV co-ords
        uv = new Vector2[verts.Length];
        //gets the size and width again
        for (int index = 0, i = 0; i <= MV.sizeZ; i++)
        {
            for (int j = 0; j <= MV.sizeX; j++)
            {
                //determines the Size of the UV for the texture based on the parameters set
                uv[index] = new Vector2((float)j / MV.sizeX, (float)i / MV.sizeZ);
                //increments the UV
                index++;
            }
        }
    }

    void Verticies()
    {
        //Mesh verticies
        verts = new Vector3[(MV.sizeX + 1) * (MV.sizeZ + 1)];

        //gets the Length of the mesh and will execute based on how large it is
        for (int index = 0, i = 0; i <= MV.sizeZ; i++)
        {
            //Ditto, but will be for the width
            for (int j = 0; j <= MV.sizeX; j++)
            {

                //gets the height of the  mesh by perlin noise.
                vertex.y = noise(i, j, 0) + noise(i, j, 1) + noise(i, j, 2);

                //sets the height of the terrain based on the values stored in vertex.y
                if (vertex.y > terrainHigh) { terrainHigh = vertex.y; }
                if (vertex.y < terrainLow) { terrainLow = vertex.y; }

                //makes a new vertex
                verts[index] = new Vector3(j, vertex.y, i);

                //increments to the next vertex
                index++;
            }
        }
    }

    void Triangles()
    {
        //gets the amount of triangles needed
        tris = new int[MV.sizeX * MV.sizeZ * 6];
        //Local variable for triangle and vertex count. this will be used throughout to calculate the size of the mesh in terms of triangles.
        int triangle = 0, vert = 0;
        //Gets the Length of the mesh and will execute based on how large it is again
        for (int i = 0; i < MV.sizeZ; i++)
        {
            //Ditto, but for width
            for (int j = 0; j < MV.sizeX; j++)
            {
                //Gets each indicie, and uses it to create a triangle to draw
                tris[triangle + 0] = vert + 0;
                tris[triangle + 1] = vert + MV.sizeX + 1;
                tris[triangle + 2] = vert + 1;
                tris[triangle + 3] = vert + 1;
                tris[triangle + 4] = vert + MV.sizeX + 1;
                tris[triangle + 5] = vert + MV.sizeX + 2;

                //Increments verticies here for each triangle
                vert++;
                //Sizes up the mesh by 6 each time
                triangle += 6;
            }
            //increments once more
            vert++;
        }
    }

    void colour()
    {
        //gets new array based on the length of the vertex array
        meshColours = new Color[verts.Length];
        for (int index = 0, i = 0; i <= MV.sizeZ; i++)
        {
            for (int j = 0; j <= MV.sizeX; j++)
            {
                //Gets the heightmap of the mesh, based on the highest points, Lowest points, and where the verticie is.
                float meshheight = Mathf.InverseLerp(terrainHigh, terrainLow, verts[index].y);

                //Causes the mesh to evaluate what parts of the mesh to colour when it uses a mesh gradiant
                meshColours[index] = MV.meshGradient.Evaluate(meshheight);
                //increments index 
                index++;
            }
        }

    }

   public void generateMesh()
    {
        //clears old mesh data
        m_TheMesh.Clear();
        //renders the mesh using a Unsigned 32-bit integer as it's format
        m_TheMesh.indexFormat = UnityEngine.Rendering.IndexFormat.UInt32;
        //we now set all of our variables as the meshes verticies, triangles, UV's and colour, then recalculate the normal map for the mesh
        m_TheMesh.vertices = verts;
        m_TheMesh.triangles = tris;
        m_TheMesh.uv = uv;
        m_TheMesh.colors = meshColours;
        m_TheMesh.RecalculateNormals();
    }

    /// <summary>
    /// This will allow a mesh to immitate the waves that can be seen in any body of water.
    /// </summary>
    /// <param name="time">the time used by the wave simulation</param>
    void wave(float time)
    {
        //for each verticie in the array
        for(int i = 0; i < verts.Length;i++)
        {
            //set the vertex to be the specific verticie
            vertex = verts[i];
            //gets the noise of the mesh, using the X and Z co-ordinates.
            float wavepattern = noise(vertex.x, vertex.z, 0) + noise(vertex.x, vertex.z, 1) + noise(vertex.x, vertex.z, 2);
            //gets the waves and multiplies the time by it. This value is then passed through a sine wave
            vertex.y = Mathf.Sin(time*wavepattern);
            //sets the height of the terrain based on the values stored in vertex.y
            if (vertex.y > terrainHigh) { terrainHigh = vertex.y; }
            if (vertex.y < terrainLow) { terrainLow = vertex.y; }
            //sets the specific verticie to be the vertex
            verts[i] = vertex;
        }
        //sets the colour
        colour();
    }

    private void OnDrawGizmos()
    {
        //returns empty if there are no verticies
        if (verts == null){return;}

        //draws gizmos if this bool is enabled,
        if (MV.drawGizmo)
        {
            //for each verticies
            for (int i = 0; i < verts.Length; i++)
            {
                //draws a sphere at the verticies location, and with a preset radius.
                Gizmos.DrawSphere(verts[i], MV.radius);
            }
        }
    }

    /// <summary>
    /// calculates the noise of the noise based on the amplification and the height values.
    /// </summary>
    /// <param name="x">Width</param>
    /// <param name="z">Height</param>
    /// <param name="Arrayindex">What amplification value to use</param>
    /// <returns>The Final result from this calculation</returns>
    float noise(float x, float z, int Arrayindex)
    {
        float Result = MV.ampvalue[Arrayindex]*Mathf.PerlinNoise(z * MV.perlinNoiseval[Arrayindex], x * MV.perlinNoiseval[Arrayindex]) * MV.height;
        return Result;
    }

    
}
