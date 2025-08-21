import i18n from 'i18next'
import { initReactI18next } from 'react-i18next'
import { resources } from './locales/translations'
import LanguageDetector from 'i18next-browser-languagedetector'

i18n
  .use(LanguageDetector)
  .use(initReactI18next)
  .init({
    resources,
    fallbackLng: "en",
    lng: navigator.language,
    debug: true,
    interpolation: {
      escapeValue: false
    }
  })
  .then(() => console.log("✅ Successfully loaded translations resources."))

export default i18n
