import { JSX } from 'react'
import { useTranslation } from 'react-i18next'

export default function ToolBar(): JSX.Element {
  const { t } = useTranslation()
  return (
    <>
      <div className="tool-bar">
        <span className="tool-bar-title no-select" draggable={false}>
          {t('my_workspace_title')}
        </span>

        <span className="tool-bar-subtitle no-select" draggable={false}>
          {t('my_workspace_title')}
        </span>
      </div>
    </>
  )
}
