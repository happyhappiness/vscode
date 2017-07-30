; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/version.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"1.11.1-dev\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_version() #0 !dbg !4 {
entry:
  ret i32 68353, !dbg !17
}

; Function Attrs: nounwind uwtable
define i8* @uv_version_string() #0 !dbg !8 {
entry:
  ret i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i32 0, i32 0), !dbg !18
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!14, !15}
!llvm.ident = !{!16}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/version.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{}
!3 = !{!4, !8}
!4 = distinct !DISubprogram(name: "uv_version", scope: !1, file: !1, line: 38, type: !5, isLocal: false, isDefinition: true, scopeLine: 38, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!8 = distinct !DISubprogram(name: "uv_version_string", scope: !1, file: !1, line: 43, type: !9, isLocal: false, isDefinition: true, scopeLine: 43, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!9 = !DISubroutineType(types: !10)
!10 = !{!11}
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !13)
!13 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!14 = !{i32 2, !"Dwarf Version", i32 4}
!15 = !{i32 2, !"Debug Info Version", i32 3}
!16 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!17 = !DILocation(line: 39, column: 3, scope: !4)
!18 = !DILocation(line: 44, column: 3, scope: !8)
