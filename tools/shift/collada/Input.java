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

/**
 *
 * @author Michael Nischt
 */
final class Input
{
  final int offset;
  final String semantic;
  final String source;
  final int set;

  Input(int offset, String semantic, String source, int set)
  {
    if(semantic == null || source == null)
    {
        throw new NullPointerException();
    }

    this.offset = offset;
    this.semantic = semantic;
    this.source = source;
    this.set = set;
  }

  boolean hasExternalSource()
  {
    return source.charAt(0) != '#';
  }

  static int groups(Input... inputs)
  {
    int groups = 0;

    for(Input input : inputs)
    {
        groups = Math.max(groups, input.offset+1);
    }
    return groups;
  }

  public static boolean compare(Input[] a, Input[] b)
  {
    if(a.length != b.length)
    {
        return false;
    }
    for(int i=0; i<a.length; i++) if (!compare(a[i], b[i]))
    {
        return false;
    }
    return true;
  }

  public static boolean compare(Input a, Input b)
  {
    return a.semantic.equals(b.semantic)
        && b.set == b.set
        && a.offset == b.offset
        && a.source.equals(b.source);
  }
}
