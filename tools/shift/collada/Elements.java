/*
 * Copyright (c) 2011 Michael Nischt
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
package org.interaction3d.assembly.tools.shift.collada;

import java.util.StringTokenizer;
import static java.lang.Integer.parseInt;
import static java.lang.Float.parseFloat;

/**
 *
 * @author Michael Nischt
 */
final class Elements
{
  public static int count(int[] counts)
  {
    int elements = 0;
    for(int c : counts)
    {
      elements += c;
    }
    return elements;
  }

  // [input][triangle][vertex]
  public static int[] parseTriangles(String text, int primitives, int inputs)
  {
    return parseIntArray(text, primitives*3*inputs);
  }

  // [input][poly][vertex]
  public static int[] parsePolylist(String text, int[] vcounts, int inputs)
  {
    int elements = 0;
    for(int c : vcounts)
    {
      elements += c;
    }
    return parseIntArray(text, elements*inputs);
  }

  public static float[] identity4x4Float()
  {
    return new float[]
    {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1,
    };
  }



  public static float[] parseFloatArray(String data, int count)
  {
    float[] array = new float[count];

    StringTokenizer tokenizer = new StringTokenizer(data);

    for(int i=0; i<count; i++)
    {
      array[i] = parseFloat(tokenizer.nextToken());
    }

    assert (!tokenizer.hasMoreTokens());

    return array;
  }

  //[index][dimension]
  public static float[] parseFloatArray(String data, int count, int dimension, int stride, int offset)
  {
    float[] array = new float[count*dimension];

    StringTokenizer tokenizer = new StringTokenizer(data);

    int index = 0;
    while(index++ < offset) tokenizer.nextToken();

    index = 0;
    for(int i=0; i<count; i++)
    {
      for(int j=0; j<dimension; j++)
      {
        array[index++] = parseFloat(tokenizer.nextToken());
      }

      for(int j=0; j<stride-dimension; j++)
      {
        tokenizer.nextToken();
      }
    }
    assert( !tokenizer.hasMoreTokens() );

    return array;
  }

  public static int[] parseIntArray(String text, int primitives)
  {
    int[] counts = new int[primitives];

    StringTokenizer tokenizer = new StringTokenizer(text);
    for(int i=0; i<primitives; i++)
    {
      assert( tokenizer.hasMoreTokens() );
      counts[i] = Integer.parseInt(tokenizer.nextToken());
    }
    assert( !tokenizer.hasMoreTokens() );

    return counts;
  }

  public static String[] parseStringArray(String text, int primitives)
  {
    String[] names = new String[primitives];

    StringTokenizer tokenizer = new StringTokenizer(text);
    for(int i=0; i<primitives; i++)
    {
      assert( tokenizer.hasMoreTokens() );
      names[i] = tokenizer.nextToken();
    }
    assert( !tokenizer.hasMoreTokens() );

    return names;
  }


  public static String[] parseStringArray(String data, int count, int dimension, int stride, int offset)
  {
    String[] array = new String[count*dimension];

    StringTokenizer tokenizer = new StringTokenizer(data);

    int index = 0;
    while(index++ < offset) tokenizer.nextToken();

    index = 0;
    for(int i=0; i<count; i++)
    {
      for(int j=0; j<dimension; j++)
      {
        array[index++] = tokenizer.nextToken();
      }

      for(int j=0; j<stride-dimension; j++)
      {
        tokenizer.nextToken();
      }
    }
    assert( !tokenizer.hasMoreTokens() );

    return array;
  }

  public static int[] parseIntArray(String data, int count, int dimension, int stride, int offset)
  {
    int[] array = new int[count*dimension];

    StringTokenizer tokenizer = new StringTokenizer(data);

    int index = 0;
    while(index++ < offset) tokenizer.nextToken();

    index = 0;
    for(int i=0; i<count-1; i++)
    {
      for(int j=0; j<dimension; j++)
      {
        array[index++] = parseInt(tokenizer.nextToken());
      }

      for(int j=0; j<stride-dimension; j++)
      {
        tokenizer.nextToken();
      }
    }

    for(int j=0; j<dimension; j++)
    {
      array[index++] = parseInt(tokenizer.nextToken());
    }

    return array;
  }

   private Elements() { /* static class */ }
}
