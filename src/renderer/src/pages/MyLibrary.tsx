import {JSX, useState} from "react"
import {FloatButton} from "antd";

export default function MyLibrary(): JSX.Element {
  const [isFloatingButtonOpened, setIsFloatingButtonOpened] = useState(false)
  return (
    <FloatButton.Group
      open={isFloatingButtonOpened}
      shape={"square"}
      trigger={"click"}
      style={{insetInlineEnd: 24}}
      icon={isFloatingButtonOpened ? 'C' : 'O'}
      onClick={() => setIsFloatingButtonOpened(!isFloatingButtonOpened)}>
      <FloatButton />
      <FloatButton />
    </FloatButton.Group>
  )
}
