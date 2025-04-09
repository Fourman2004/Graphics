using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(MeshFilter))]
public class MeshFunnygen : MonoBehaviour
{
    [Header("The Mesh")]
    Mesh m_TheMesh;

    [SerializeField,Header("mesh Data")]
    Vector3[] verts;
    [SerializeField]
    int[] tris;

    public int sizeX, sizeZ;
    public float radial;
    // Start is called before the first frame update
    void Start()
    {
        m_TheMesh = new Mesh();
        GetComponent<MeshFilter>().mesh = m_TheMesh;
       dataForTerrain();
        generateMesh();
    }

    void dataForTerrain()
    {

        verts = new Vector3[(sizeX + 1) * (sizeZ + 1)];

       
        for (int index = 0, i = 0; i <= sizeZ; i++)
        {
            for (int j = 0; j <= sizeX; j++)
            {
                verts[index] = new Vector3(j, 0, i);
                index++;
            }
        }

        for (int index = 0, i = 0; i <= sizeX; i++)
        {
            for (int j = 0; j <= sizeX; j++)
            {
                
                index++;
            }
        }
    }

    void generateMesh()
    {
        m_TheMesh.Clear();

        m_TheMesh.vertices = verts;
        m_TheMesh.triangles = tris;
        m_TheMesh.RecalculateNormals();
    }

    private void OnDrawGizmos()
    {
        if (verts == null){return;}

        for (int i = 0; i < verts.Length; i++)
        {
            Gizmos.DrawSphere(verts[i],radial);
        }
    }
}
