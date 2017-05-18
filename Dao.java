package dao;

import entity.Book;
import util.HibernateUtil;
import java.util.ArrayList;
import java.util.List;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

/**
 * Created by Fahriye on 10.8.2016.
 */
public class Dao {
    public void addBook(Book book) {
        Transaction tarns = null;
        Session session = HibernateUtil.getSessionFactory().openSession();
        try {
            tarns = session.beginTransaction();
            session.save(book);
            session.getTransaction().commit();
        } catch (RuntimeException e) {
            if (tarns != null) {
                tarns.rollback();
            }
            e.printStackTrace();
        } finally {
            session.flush();
            session.close();
        }
    }

    public void deleteBook(int book_id) {
        Transaction tarns = null;
        Session session = HibernateUtil.getSessionFactory().openSession();
        try {
            tarns = session.beginTransaction();
            Book book = (Book) session.load(Book.class, book_id);
            session.delete(book);
            session.getTransaction().commit();
        } catch (RuntimeException e) {
            if (tarns != null) {
                tarns.rollback();
            }
            e.printStackTrace();
        } finally {
            session.flush();
            session.close();
        }
    }

    public void updateBook(Book book) {
        Transaction tarns = null;
        Session session = HibernateUtil.getSessionFactory().openSession();
        try {
            tarns = session.beginTransaction();
            session.update(book);
            session.getTransaction().commit();
        } catch (RuntimeException e) {
            if (tarns != null) {
                tarns.rollback();
            }
            e.printStackTrace();
        } finally {
            session.flush();
            session.close();
        }
    }

    public List<Book> getAllBooks() {
        List users = new ArrayList<Book>();
        Transaction tarns = null;
        Session session = HibernateUtil.getSessionFactory().openSession();
        try {
            tarns = session.beginTransaction();
            users = session.createQuery("select b.book_id from entity.Book b").list();
        } catch (RuntimeException e) {
            e.printStackTrace();
        } finally {
            session.flush();
            session.close();
        }
        return users;
    }

    public List<Book> getBookById(int bookid) {
        System.out.println(bookid);
//        Book book = null;
        Transaction tarns = null;
        Session session = HibernateUtil.getSessionFactory().openSession();
        try {
            tarns = session.beginTransaction();
            String queryString = "from entity.Book where book_id = :id";
            Query query = session.createQuery(queryString);
            query.setInteger("id",(bookid));
            //book = (Book) query.uniqueResult();
            List<Book> list = query.list();
            if (list.size() > 0) {
                return list;
            }
        } catch (RuntimeException e) {
            e.printStackTrace();
        } finally {
            session.flush();
            session.close();
        }
        return null;
    }
}