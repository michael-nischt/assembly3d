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

import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;

import static java.lang.Integer.parseInt;
import static java.lang.Float.parseFloat;

final class XmlAttributes
{
  private final NamedNodeMap attributes;

  public XmlAttributes(Node node)
  {
    this(node.getAttributes());
  }

  public XmlAttributes(NamedNodeMap attributes)
  {
    if (attributes == null)
    {
      throw new NullPointerException();
    }
    this.attributes = attributes;
  }

  public String getString(String name)
  {
    Node node = attributes.getNamedItem(name);
    return node.getNodeValue();
  }

  public String getString(String name, String value)
  {
    Node node = attributes.getNamedItem(name);
    if (node == null)
    {
      return value;
    }
    return node.getNodeValue();
  }

  public int getInt(String name)
  {
    Node node = attributes.getNamedItem(name);
    return parseInt(node.getNodeValue());
  }

  public int getInt(String name, int value)
  {
    Node node = attributes.getNamedItem(name);
    if (node == null)
    {
      return value;
    }
    return parseInt(node.getNodeValue());
  }

  public float getFloat(String name)
  {
    Node node = attributes.getNamedItem(name);
    return parseFloat(node.getNodeValue());
  }

  public float getFloat(String name, float value)
  {
    Node node = attributes.getNamedItem(name);
    if (node == null)
    {
      return value;
    }
    return parseFloat(node.getNodeValue());
  }
}
