#pragma once

template <typename T>
class ContainerKeyRange
{
public:
   ContainerKeyRange(T& data) : m_data{data}
   {
   }

   auto begin()
   {
      return m_data.keyBegin();
   }

   auto end()
   {
      return m_data.keyEnd();
   }

private:
   T& m_data;
};

template <typename T>
class ContainerKeyValueRange
{
public:
   ContainerKeyValueRange(T& data) : m_data{data}
   {
   }

   auto begin()
   {
      return m_data.keyValueBegin();
   }

   auto end()
   {
      return m_data.keyValueEnd();
   }

private:
   T& m_data;
};

template <class C>
class PSet : public QSet<typename C::key_type>
{
public:
   PSet(const C& container)
   {
      for (const C::key_type& key : ContainerKeyRange(container))
      {
         insert(key);
      }
   }
   template<typename Pred>
   PSet(const C& container, Pred pred)
   {
      for (const C::key_type& key : ContainerKeyRange(container))
      {
         if (pred(key))
         {
            insert(key);
         }
      }
   }
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
