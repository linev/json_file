#pragma GCC diagnostic ignored "-Wunused-parameter"

// Author: Sergey Linev  8.07.2022

/*************************************************************************
 * Copyright (C) 1995-2022, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//________________________________________________________________________
//
// TKeyJSON is represents one block of data in TXMLFile
// Normally this block corresponds to data of single object like histogram,
// TObjArray and so on.
//________________________________________________________________________

#include "TKeyJSON.h"

namespace jsonio {

const char *Root = "root";
const char *Setup = "setup";
const char *ClassVersion = "version";
const char *IOVersion = "version";
const char *OnlyVersion = "Version";
const char *Ptr = "ptr";
const char *Ref = "ref";
const char *Null = "null";
const char *IdBase = "id";
const char *Size = "size";
const char *Xmlobject = "XmlObject";
const char *Xmlkey = "XmlKey";
const char *Cycle = "cycle";
const char *XmlBlock = "XmlBlock";
const char *Zip = "zip";
const char *Object = "Object";
const char *ObjClass = "class";
const char *Class = "Class";
const char *Member = "Member";
const char *Item = "Item";
const char *Name = "name";
const char *Title = "title";
const char *CreateTm = "created";
const char *ModifyTm = "modified";
const char *ObjectUUID = "uuid";
const char *Type = "type";
const char *Value = "value";
const char *v = "v";
const char *cnt = "cnt";
const char *True = "true";
const char *False = "false";
const char *SInfos = "StreamerInfos";

const char *Array = "Array";
const char *Bool = "Bool_t";
const char *Char = "Char_t";
const char *Short = "Short_t";
const char *Int = "Int_t";
const char *Long = "Long_t";
const char *Long64 = "Long64_t";
const char *Float = "Float_t";
const char *Double = "Double_t";
const char *UChar = "UChar_t";
const char *UShort = "UShort_t";
const char *UInt = "UInt_t";
const char *ULong = "ULong_t";
const char *ULong64 = "ULong64_t";
const char *String = "string";
const char *CharStar = "CharStar";
};


#include "TBufferJSON.h"
#include "TJSONFile.h"
#include "TClass.h"
#include "TROOT.h"

ClassImp(TKeyJSON);

////////////////////////////////////////////////////////////////////////////////
/// Creates TKeyJSON and convert object data to xml structures

TKeyJSON::TKeyJSON(TDirectory *mother, Long64_t keyid, const TObject *obj, const char *name, const char *title)
   : TKey(mother), fKeyNode(nullptr), fKeyId(keyid), fSubdir(kFALSE)
{
   if (name) {
      SetName(name);
   } else if (obj) {
      SetName(obj->GetName());
      fClassName = obj->ClassName();
   } else
      SetName("Noname");

   if (title)
      SetTitle(title);

   fCycle = GetMotherDir()->AppendKey(this);

   //TXMLEngine *xml = XMLEngine();
   //if (xml)
   //   fKeyNode = xml->NewChild(nullptr, nullptr, xmlio::Xmlkey);

   fDatime.Set();

   StoreObject(obj, nullptr, kTRUE);
}

////////////////////////////////////////////////////////////////////////////////
/// Creates TKeyJSON and convert object data to xml structures

TKeyJSON::TKeyJSON(TDirectory *mother, Long64_t keyid, const void *obj, const TClass *cl, const char *name,
                 const char *title)
   : TKey(mother), fKeyNode(nullptr), fKeyId(keyid), fSubdir(kFALSE)
{
   if (name && *name)
      SetName(name);
   else
      SetName(cl ? cl->GetName() : "Noname");

   if (title)
      SetTitle(title);

   fCycle = GetMotherDir()->AppendKey(this);

   //TXMLEngine *xml = XMLEngine();
   //if (xml)
   //   fKeyNode = xml->NewChild(nullptr, nullptr, xmlio::Xmlkey);

   fDatime.Set();

   StoreObject(obj, cl, kFALSE);
}

////////////////////////////////////////////////////////////////////////////////
/// Creates TKeyJSON and takes ownership over xml node, from which object can be restored

TKeyJSON::TKeyJSON(TDirectory *mother, Long64_t keyid, void *keynode)
   : TKey(mother), fKeyNode(keynode), fKeyId(keyid), fSubdir(kFALSE)
{
/*   TXMLEngine *xml = XMLEngine();

   SetName(xml->GetAttr(keynode, xmlio::Name));

   if (xml->HasAttr(keynode, xmlio::Title))
      SetTitle(xml->GetAttr(keynode, xmlio::Title));

   fCycle = xml->GetIntAttr(keynode, xmlio::Cycle);

   if (xml->HasAttr(keynode, xmlio::CreateTm)) {
      TDatime tm(xml->GetAttr(keynode, xmlio::CreateTm));
      fDatime = tm;
   }

   XMLNodePointer_t objnode = xml->GetChild(keynode);
   xml->SkipEmpty(objnode);

   fClassName = xml->GetAttr(objnode, xmlio::ObjClass);
*/
}

////////////////////////////////////////////////////////////////////////////////
/// TKeyJSON destructor

TKeyJSON::~TKeyJSON()
{
/*   if (fKeyNode) {
      TXMLEngine *xml = XMLEngine();
      if (xml) {
         xml->FreeNode(fKeyNode);
      } else {
         TXMLEngine xml_;
         xml_.FreeNode(fKeyNode);
      }
   }
*/
}

////////////////////////////////////////////////////////////////////////////////
/// Delete key from current directory
/// Note: TKeyJSON object is not deleted. You still have to call "delete key"

void TKeyJSON::Delete(Option_t * /*option*/)
{
/*   TXMLEngine *xml = XMLEngine();
   if (fKeyNode && xml) {
      xml->FreeNode(fKeyNode);
      fKeyNode = nullptr;
   }
*/
   fMotherDir->GetListOfKeys()->Remove(this);
}

////////////////////////////////////////////////////////////////////////////////
/// Stores keys attributes in key node

void TKeyJSON::StoreKeyAttributes()
{
/*   TXMLEngine *xml = XMLEngine();
   TXMLFile *f = (TXMLFile *)GetFile();
   if (!f || !xml || !fKeyNode)
      return;

   xml->NewAttr(fKeyNode, nullptr, xmlio::Name, GetName());

   xml->NewIntAttr(fKeyNode, xmlio::Cycle, fCycle);

   if (f->GetIOVersion() > 1) {
      if (strlen(GetTitle()) > 0)
         xml->NewAttr(fKeyNode, nullptr, xmlio::Title, GetTitle());
      if (f->TestBit(TFile::kReproducible))
         xml->NewAttr(fKeyNode, nullptr, xmlio::CreateTm, TDatime((UInt_t) 1).AsSQLString());
      else
         xml->NewAttr(fKeyNode, nullptr, xmlio::CreateTm, fDatime.AsSQLString());
   }
*/
}

////////////////////////////////////////////////////////////////////////////////
///  convert object to xml structure and keep this structure in key

void TKeyJSON::StoreObject(const void *obj, const TClass *cl, Bool_t check_tobj)
{
/*
   TXMLFile *f = (TXMLFile *)GetFile();
   TXMLEngine *xml = XMLEngine();
   if (!f || !xml || !fKeyNode)
      return;

   if (obj && check_tobj) {
      TClass *actual = TObject::Class()->GetActualClass((TObject *)obj);
      if (!actual) {
         actual = TObject::Class();
      } else if (actual != TObject::Class())
         obj = (void *)((Longptr_t)obj - actual->GetBaseClassOffset(TObject::Class()));
      cl = actual;
   }

   StoreKeyAttributes();

   TBufferXML buffer(TBuffer::kWrite, f);
   buffer.InitMap();
   if (f->GetIOVersion() == 1)
      buffer.SetBit(TBuffer::kCannotHandleMemberWiseStreaming, kFALSE);

   XMLNodePointer_t node = buffer.XmlWriteAny(obj, cl);

   if (node)
      xml->AddChildFirst(fKeyNode, node);

   buffer.XmlWriteBlock(fKeyNode);

   if (cl)
      fClassName = cl->GetName();
*/
}

////////////////////////////////////////////////////////////////////////////////
/// update key attributes in key node

void TKeyJSON::UpdateAttributes()
{
/*
   TXMLEngine *xml = XMLEngine();
   if (!xml || !fKeyNode)
      return;

   xml->FreeAllAttr(fKeyNode);

   StoreKeyAttributes();
*/
}

////////////////////////////////////////////////////////////////////////////////
/// updates object, stored in the node
/// Used for TDirectory data update

void TKeyJSON::UpdateObject(TObject *obj)
{
/*
   TXMLFile *f = (TXMLFile *)GetFile();
   TXMLEngine *xml = XMLEngine();
   if (!f || !xml || !obj || !fKeyNode)
      return;

   XMLNodePointer_t objnode = xml->GetChild(fKeyNode);
   xml->SkipEmpty(objnode);

   if (!objnode)
      return;

   xml->UnlinkNode(objnode);
   xml->FreeNode(objnode);

   xml->FreeAllAttr(fKeyNode);

   StoreObject(obj, nullptr, kTRUE);
*/
}

////////////////////////////////////////////////////////////////////////////////
/// To read an object from the file.
/// The object associated to this key is read from the file into memory.
/// Before invoking this function, obj has been created via the
/// default constructor.

Int_t TKeyJSON::Read(TObject *tobj)
{
   if (!tobj)
      return 0;

   void *res = JsonReadAny(tobj, nullptr);

   return !res ? 0 : 1;
}

////////////////////////////////////////////////////////////////////////////////
/// read object derived from TObject class, from key
/// if it is not TObject or in case of error, return nullptr

TObject *TKeyJSON::ReadObj()
{
   TObject *tobj = (TObject *)JsonReadAny(nullptr, TObject::Class());

   if (tobj) {
      if (gROOT->GetForceStyle())
         tobj->UseCurrentStyle();
      if (tobj->IsA() == TDirectoryFile::Class()) {
         TDirectoryFile *dir = (TDirectoryFile *)tobj;
         dir->SetName(GetName());
         dir->SetTitle(GetTitle());
         dir->SetSeekDir(GetKeyId());
         // set mother before reading keys
         dir->SetMother(fMotherDir);
         dir->ReadKeys();
         fMotherDir->Append(dir);
         fSubdir = kTRUE;
      }
   }

   return tobj;
}

////////////////////////////////////////////////////////////////////////////////
/// read object derived from TObject class, from key
/// if it is not TObject or in case of error, return nullptr

TObject *TKeyJSON::ReadObjWithBuffer(char * /*bufferRead*/)
{
   TObject *tobj = (TObject *)JsonReadAny(nullptr, TObject::Class());

   if (tobj) {
      if (gROOT->GetForceStyle())
         tobj->UseCurrentStyle();
      if (tobj->IsA() == TDirectoryFile::Class()) {
         TDirectoryFile *dir = (TDirectoryFile *)tobj;
         dir->SetName(GetName());
         dir->SetTitle(GetTitle());
         dir->SetSeekDir(GetKeyId());
         // set mother before reading keys
         dir->SetMother(fMotherDir);
         dir->ReadKeys();
         fMotherDir->Append(dir);
         fSubdir = kTRUE;
      }
   }

   return tobj;
}

////////////////////////////////////////////////////////////////////////////////
/// read object of any type

void *TKeyJSON::ReadObjectAny(const TClass *expectedClass)
{
   void *res = JsonReadAny(nullptr, expectedClass);

   if (res && (expectedClass == TDirectoryFile::Class())) {
      TDirectoryFile *dir = (TDirectoryFile *)res;
      dir->SetName(GetName());
      dir->SetTitle(GetTitle());
      dir->SetSeekDir(GetKeyId());
      // set mother before reading keys
      dir->SetMother(fMotherDir);
      dir->ReadKeys();
      fMotherDir->Append(dir);
      fSubdir = kTRUE;
   }

   return res;
}

////////////////////////////////////////////////////////////////////////////////
/// read object from key and cast to expected class

void *TKeyJSON::JsonReadAny(void *obj, const TClass *expectedClass)
{
/*   if (!fKeyNode)
      return obj;

   TXMLFile *f = (TXMLFile *)GetFile();
   TXMLEngine *xml = XMLEngine();
   if (!f || !xml)
      return obj;

   TBufferXML buffer(TBuffer::kRead, f);
   buffer.InitMap();
   if (f->GetIOVersion() == 1)
      buffer.SetBit(TBuffer::kCannotHandleMemberWiseStreaming, kFALSE);

   XMLNodePointer_t blocknode = xml->GetChild(fKeyNode);
   xml->SkipEmpty(blocknode);
   while (blocknode) {
      if (strcmp(xml->GetNodeName(blocknode), xmlio::XmlBlock) == 0)
         break;
      xml->ShiftToNext(blocknode);
   }
   buffer.XmlReadBlock(blocknode);

   XMLNodePointer_t objnode = xml->GetChild(fKeyNode);
   xml->SkipEmpty(objnode);

   TClass *cl = nullptr;
   void *res = buffer.JsonReadAny(objnode, obj, &cl);

   if (!cl || !res)
      return obj;

   Int_t delta = 0;

   if (expectedClass) {
      delta = cl->GetBaseClassOffset(expectedClass);
      if (delta < 0) {
         if (!obj)
            cl->Destructor(res);
         return nullptr;
      }
      if (cl->GetState() > TClass::kEmulated && expectedClass->GetState() <= TClass::kEmulated) {
         // we cannot mix a compiled class with an emulated class in the inheritance
         Warning("JsonReadAny", "Trying to read an emulated class (%s) to store in a compiled pointer (%s)",
                 cl->GetName(), expectedClass->GetName());
      }
   }

   return ((char *)res) + delta;
*/

   return nullptr;
}
